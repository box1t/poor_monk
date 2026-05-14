
- matplotlib строит графики на Figure. каждый из них содержит один или более Axes.

# The explicit and the implicit interfaces

- two ways to use Matplotlib:
	- Explicitly create Figures and Axes, and call methods on them (the "object-oriented (OO) style").
    - Rely on pyplot to implicitly create and manage the Figures and Axes, and use pyplot functions for plotting.

- Чем отличается подход к построению графиков с pyplot от Figures and Axes в matplotlib?
	- object-oriented style (OO) - figures and axes - explicit way to create plots
	- pyplot - implicit way to create plots

- Axes - зона, где точки могут быть специфицированы в терминах x-y координат.
- Простейший путь создания Figure с Axes - sublots().
	- figure допускается создать несколькими способами: 
		- явно, plt.figure() - пустой шаблон figure без axes.
		- неявно, на основе subplots(), subplot_mosaic()




# Axes = subplots
- 
- Axes это gateway для создания визуализации данных.
- Axes размещается на figure. Есть много методов для добавления данных на Axes.
- Обычно Axes идет в паре с Axis. 
Axis задает систему координат, включает в себя методы размещения аннотаций x- and y-labels, titles, and legends.

# Artists

- Почти все объекты взаимодействия в matplotlib - подклассы класса Artist, включая Figure и Axes.
- При этом Axis тоже входит в множество подклассов Artist.


