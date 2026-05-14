
- we can access the property of an object by accessing it as an attribute.
- Series - одномерный размеченный (как?) массив, способный хранить любой тип данных. 
- The axis labels are collectively referred to as the index. (Метки осей вместе называются индексом.)
- как создать Series / DataFrame?
	- pd.Series(data, index=index)
	- pd.DataFrame(data, index=index, columns=columns)


## pd/Docs/user_guide
- Основной метод создания Series содержит в себе аргументы: s=pd.Series(data, index=index)
	- Если data это ndarray, то число переменных в data и в index должно совпадать.
	- Если data это словарь, то index первоначально подставится из значений слева от двоеточия в словаре, и только затем из значений index, если переданы.
	- Если значение скалярное, индекс должен быть предоставлен, притом скалярное значение повторится в количестве согласно длине index. 



## Kaggle. Lesson 2

- Какие парадигмы индексации в pandas?
	- 1. 'iloc' - Index-based selection: значима позиция данных. [0:9]
		- iloc uses the Python stdlib indexing scheme, where the first element of the range is included and the last one excluded c
	- 2. 'loc' - Label-based selection: значим индекс данных, не позиция. [0:10] - first one and last one included.
- the Index is first build with the keys from the dictionary, second - reindexed from "index" values.




- Что общего у loc и iloc?
	- both are row-first, column-second
		- easier to retrieve rows, harder to get columns.
	- это противоположно нативному python.

- Hint: you may use loc or iloc. When working on the answer this question and the several of the ones that follow, keep the following "gotcha" described in the tutorial:
   - iloc uses the Python stdlib indexing scheme, where the first element of the range is included and the last one excluded. loc, meanwhile, indexes inclusively.
   - This is particularly confusing when the DataFrame index is a simple numerical list, e.g. 0,...,1000. In this case df.iloc[0:1000] will return 1000 entries, while df.loc[0:1000] return 1001 of them! To get 1000 elements using loc, you will need to go one lower and ask for df.iloc[0:999].



- Как связаны loc, iloc и ':'?
	- ':' - range of values


- Отличие операторов доступа iloc и loc?
	- iloc упрощён на фоне loc: игнорирует индексы датасета.
	- как это проявляется?
		- loc использует информацию в индексах для выполнения работы.
		- если в датасетах есть индексы, удобнее loc. 
		


