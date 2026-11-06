```c++
struct Vec{
	float x, y;
};
Vec operator+ (const Vec& l, const Vec& r){
	return {l.x + r.x, l.y + r.y};
}
Vec& operator+= (Vec& l, const Vec& r){
	l.x += r.x;
	l.y += r.y;
	return l;
}
std::ostream& operator <<(std::ostream& os, const Vec& v){
	os << v.x << ',' << v.y;
	return os;
}
bool operator< (const Vec& l, const Vec& r){
	return l.x != r.x ? l.x < r.x : l.y < r.y;
}
bool operator==(const Vec& l, const Vec& r){
	return l.x == r.x && l.y == r.y;
}
bool operator> (const Vec& l, const Vec& r) { return r < l; }
bool operator<=(const Vec& l, const Vec& r) { return !(l > r); }
bool operator>=(const Vec& l, const Vec& r) { return !(l < r); }
bool operator!=(const Vec& l, const Vec& r) { return !(l == r); }
```
