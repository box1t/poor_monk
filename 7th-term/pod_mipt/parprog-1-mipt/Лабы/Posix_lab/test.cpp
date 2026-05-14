#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#include <chrono>
#include <thread>
#include <mutex>

#define A_DEF -3.99
#define B_DEF 3.0
#define SPK 10
#define MAX_GLOBAL_TASKS 50
#define RESULT 2.37030912828138

//#define MS_DELAY 5
//#define SHOW_LOG
//#define SHOW_LOG_SDAT_ACCESS

double F(double x){
	return sin(1/((x+4)*(x+4)*(x+4)));
}

double dS(double x1, double x2){
	double dX = x2 - x1;
    	double f = F(x1 + dX / 2);
	return f * dX;
}

struct Interval{
    	double A,B,fA,fB,s;
};

#ifdef SHOW_LOG
    	#define LOG(msg) std::cout << msg << std::endl;
#else
   	#define LOG(msg)
#endif

#ifdef SHOW_LOG_SDAT_ACCESS
   	#define LOG_CA(msg) std::cout << msg << std::endl;
#else
	#define LOG_CA(msg)
#endif

#define PUT_INTO_LOCAL_STACK(A_,B_,fA_,fB_,s_) 	    				\
	do {                            					\
		stk[sp].A=A_;                        				\
		stk[sp].B=B_;                        				\
		stk[sp].fA=fA_;                      				\
		stk[sp].fB=fB_;                      				\
		stk[sp].s=s_;                        				\
		sp++;                               				\
	} while (0)

#define GET_FROM_LOCAL_STACK(A_,B_,fA_,fB_,s_)     				\
   	do {									\
		sp--;                               				\
		A_=stk[sp].A;                        				\
		B_=stk[sp].B;                        				\
		fA_=stk[sp].fA;                      				\
		fB_=stk[sp].fB;                      				\
		s_=stk[sp].s;                        				\
	} while(0)

#define PUT_INTO_GLOBAL_STACK(A_, B_, fA_, fB_, s_)				\
	do {									\
		sdat.stk[sdat.sp].A=A_;                        			\
		sdat.stk[sdat.sp].B=B_;                        			\
		sdat.stk[sdat.sp].fA=fA_;                      			\
		sdat.stk[sdat.sp].fB=fB_;                      			\
		sdat.stk[sdat.sp].s=s_;                    	 		\
		sdat.sp++;                               			\
	} while (0)

#define ADD_TO_GLOBAL_SUMM(s)							\
	do {									\
		sdat.sem_sum.lock();						\
		LOG(rank<<"\t Add local "<<s<<" to global "<<sdat.s_all)	\
		sdat.s_all += s;						\
		sdat.sem_sum.unlock();						\
	} while(0)

#define PUT_OFFLINE()								\
	do {									\
		LOG_CA(rank << "\t OFFLINE" << sdat.sp)				\
		sdat.sem_list.lock();						\
		sdat.nactive--;							\
		LOG_CA(rank << "\t CHECK "<< sdat.nactive << " " << sdat.sp)	\
		if((!sdat.nactive) && (!sdat.sp)){				\
			LOG(rank<<"\t Put termination tasks in global stack");	\
			LOG_CA(rank<<"\t START TERMINATION")			\
			for(int i=0; i < sdat.nproc; i++){			\
				PUT_INTO_GLOBAL_STACK(2,1,0,0,0);		\
			}							\
			sdat.sem_task_present.unlock();				\
		}								\
		sdat.sem_list.unlock();						\
	} while(0)

#define GET_FROM_GLOBAL_STACK(A_,B_,fA_,fB_,s_)					\
	do {									\
		LOG(rank<<"\t Seek for new Global Task")			\
		sdat.sem_task_present.lock();					\
		LOG(rank<<"\t See new Global Task. Try to get it")		\
		LOG_CA(rank<<"\t GET GLOBAL\t"<<sdat.sp)			\
		sdat.sem_list.lock();						\
										\
		sdat.sp--;							\
		A_ = sdat.stk[sdat.sp].A;					\
		B_ = sdat.stk[sdat.sp].B;					\
		fA_ = sdat.stk[sdat.sp].fA;					\
		fB_ = sdat.stk[sdat.sp].fB;					\
		s_ = sdat.stk[sdat.sp].s;					\
										\
		if(sdat.sp) {							\
			LOG(rank<<"\t More Global Tasks here! Come one next!")	\
			sdat.sem_task_present.unlock();				\
		}								\
										\
		if(!(A_ > B_)) {						\
			LOG(rank<<"\t Valid task. Stay active")			\
			sdat.nactive++;						\
		}								\
										\
		sdat.sem_list.unlock();						\
										\
	} while(0)


struct SharedData{
	Interval stk[MAX_GLOBAL_TASKS];
	int sp=0;
	int nactive=0;
	int nproc;
	double s_all=0;
	double dI;

	std::mutex sem_sum;
	std::mutex sem_list;
	std::mutex sem_task_present;
};

void worker(SharedData& sdat, int rank){
	double A,B,C,fA,fB,fC,sAB,sAC,sCB,sACB;
	Interval stk[MAX_GLOBAL_TASKS];
	int sp = 0;
	double s = 0;
	LOG(rank << "\t PROCESS STARTED")

	while(1){
		GET_FROM_GLOBAL_STACK(A,B,fA,fB,sAB);
		if(A>B) {
			LOG(rank << "\t TERMINATED")
			break;
		}
		s = 0;
		while(1){
			#ifdef MS_DELAY
			std::this_thread::sleep_for(std::chrono::milliseconds(MS_DELAY));
			#endif
			C = (A+B)/2;
	        	fC = F(C);
        		sAC = dS(A,C);
        		sCB = dS(C,B);
        		sACB = sAC + sCB;

        		if(fabs(sAB-sACB) >= sdat.dI * fabs(sACB)){
            			PUT_INTO_LOCAL_STACK(A, C, fA, fC, sAC);
            			A=C;
            			fA=fC;
            			sAB=sCB;
        		}
        		else{
            			s += sACB;
				if(sp==0) break;
				GET_FROM_LOCAL_STACK(A, B, fA, fB, sAB);
      		  	}

			if((sp>SPK) && (!sdat.sp)){
				LOG(rank << "\t Start putting tasks into global stack")
				LOG_CA(rank << "\t PUT GLOBAL" <<sdat.sp)
				sdat.sem_list.lock();
				while((sp>1) && (sdat.sp < MAX_GLOBAL_TASKS)){
					PUT_INTO_GLOBAL_STACK(A, B, fA, fB, sAB);
					GET_FROM_LOCAL_STACK(A, B, fA, fB, sAB);
				}
				sdat.sem_task_present.unlock();
				sdat.sem_list.unlock();
			}
		}
		ADD_TO_GLOBAL_SUMM(s);
		PUT_OFFLINE();
	}
}

int main(int argc, char** argv) {
	const int size = std::stoi(argv[1]);

	SharedData sdat;
	sdat.dI = std::stod(argv[2]);
	sdat.nproc = size;

	const double dX = (B_DEF - A_DEF) / size;
	double A = A_DEF;
	double B = A + dX;
	for (int i = 0; i < size; i++){
		PUT_INTO_GLOBAL_STACK(A, B, F(A), F(B), dS(A,B));
		A = B;
		B += dX;
	}

    	std::vector<std::thread> threads;

	LOG("PROGRAMM STARTED")
	auto start = std::chrono::high_resolution_clock::now();	
    	for (int i = 0; i < size; ++i) {
        	threads.emplace_back(worker, std::ref(sdat), i);
    	}
    	for(auto& th: threads){
        	th.join();
    	}
	auto end = std::chrono::high_resolution_clock::now();
	LOG("PROGRAMM FINISHED")
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    	std::cout << "TIME: " << duration.count() << "ns" << std::endl;

    	std::cout << std::fixed << std::setprecision (15) << sdat.s_all << std::endl;
    	std::cout << std::fixed << std::setprecision (15) << RESULT << std::endl;
    	std::cout << std::fixed << std::setprecision (15) << fabs(RESULT - sdat.s_all) << std::endl;
    	return 0;
}
