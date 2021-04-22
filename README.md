# CSP_2021_project
Проект по курсу "Программирование систем управления". \
Отчет по проекту - 'ПСУ 2021'\
Задание в 'Tasks.pdf'. \
В папке 'solution\matlab' находятся модели в Matlab. \
В папке 'solution\Qt\Qt_src' ноходятся исходники в Qt Creator 4.14.2 (открывается в 5.15.2) - среда близкая к симуляции работы МК. \
Отчет делается по ссылке [20.04.2021]: https://docs.google.com/document/d/1ZN-TGgPqDpFwOiY1Opg-XCvIx1ZgOiNofcdMYTR4LIc/edit \

Для выбора режима моделирования системы (непрерывной или дискретных 5гц, 25Гц, 100Гц) в Qt в файле '\solution\Qt\Qt_src\widget.cpp' задать modelType из {CONTINUOUS, MODELD5HZ, MODELD25HZ, MODELD100HZ}. Например: \
modelType = MODELD100HZ
