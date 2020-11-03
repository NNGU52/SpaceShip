# SpaceShip
Моделирование спуска космического корабля с орбиты с учетом влияния земной атмосферы

## Постановка задачи
Физически смоделировать движение космического корабля по круговой или эллиптической орбите вокруг Земли на таком расстоянии от нее, что сопротивлением атмосферы можно пренебречь. После 1 – 2 оборотов такого движения включить на время t_1 постоянную силу торможения и проверить, как будет изменяться траектория движения космического тела. До падения на Землю учитывать силу лобового сопротивления атмосферы.

Физически смоделировать спуск космического тела, приближающегося к Земле из бесконечности при таком же влиянии атмосферы.

Разработать программу, с помощью которой можно визуально пронаблюдать за тем,  как будет происходить в действительности заранее спланированный и рассчитанный космический полет. Показать Землю, траекторию полета, а также графики зависимости энергий(кинетической, потенциальной, полной) и скорости от времени.

## Схема работы программы
<p align="center">Считывание начальных условий</p>
<p align="center">↓</p>
<p align="center">Пересчет координат с помощью метода Рунге-Кута и значений энергий</p>
<p align="center">↓</p>
<p align="center">Отрисовка траектории движения космического тела</p>
<p align="center">↓</p>
<p align="center">Вывод графиков энергий</p>
<p align="center">↓</p>
<p align="center">Отрисовка Земли</p>
<p align="center">↓</p>
<p align="center">Отрисовка космического аппарата</p>

## Работа программы
Спутник движется по круговой орбите с постоянной скоростью, неизменной высотой и сохраняющейся полной энергией. Это является теоретически абсолютно верным, и подтверждается на практике. При движении по второму кругу, заметных глазу смещений по траектории замечено не было, значит можно говорить о достаточной точности расчетов.
<p align="center"><img src="https://github.com/NNGU52/SpaceShip/blob/main/screenshots/1.%20%D0%94%D0%B2%D0%B8%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5%20%D0%BA%D0%BE%D1%81%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B3%D0%BE%20%D0%BA%D0%BE%D1%80%D0%B0%D0%B1%D0%BB%D1%8F%20%D0%BF%D0%BE%20%D0%BA%D1%80%D1%83%D0%B3%D0%BE%D0%B2%D0%BE%D0%B9%20%D0%BE%D1%80%D0%B1%D0%B8%D1%82%D0%B5.png"/></p>

Известно, что при движении с меньшей скоростью, спутник должен начать движение по эллиптической орбите. Это было реализовано в программе также на двух оборотах вокруг Земли.
<p align="center"><img src="https://github.com/NNGU52/SpaceShip/blob/main/screenshots/2.%20%D0%94%D0%B2%D0%B8%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5%20%D0%BA%D0%BE%D1%81%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B3%D0%BE%20%D0%BA%D0%BE%D1%80%D0%B0%D0%B1%D0%BB%D1%8F%20%D0%BF%D0%BE%20%D1%8D%D0%BB%D0%BB%D0%B8%D0%BF%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B9%20%D0%BE%D1%80%D0%B1%D0%B8%D1%82%D0%B5.png"/></p>

Далее был проделан опыт с недостаточной скоростью для движения спутника по орбите.
<p align="center"><img src="https://github.com/NNGU52/SpaceShip/blob/main/screenshots/3.%20%D0%9F%D0%B0%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5%20%D0%BA%D0%BE%D1%81%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B3%D0%BE%20%D0%BA%D0%BE%D1%80%D0%B0%D0%B1%D0%BB%D1%8F%20%D0%BD%D0%B0%20%D0%BF%D0%BE%D0%B2%D0%B5%D1%80%D1%85%D0%BD%D0%BE%D1%81%D1%82%D1%8C%20%D0%97%D0%B5%D0%BC%D0%BB%D0%B8%20%D0%BF%D1%80%D0%B8%20%D1%81%D0%BA%D0%BE%D1%80%D0%BE%D1%81%D1%82%D0%B8%2C%20%D0%BD%D0%B5%D0%B4%D0%BE%D1%81%D1%82%D0%B0%D1%82%D0%BE%D1%87%D0%BD%D0%BE%D0%B9%20%D0%B4%D0%BB%D1%8F%20%D0%BF%D0%BE%D0%BB%D0%B5%D1%82%D0%B0%20%D0%BF%D0%BE%20%D0%BE%D1%80%D0%B1%D0%B8%D1%82%D0%B5%20(%D0%BD%D0%B0%20%D0%B2%D1%8B%D1%81%D1%82%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%BD%D0%BE%D0%B9%20%D0%B2%D1%8B%D1%81%D0%BE%D1%82%D0%B5).png"/></p>

Также в ходе проверки правильности работы программы требуется исследовать движение спутника при включении тормозного двигателя.
<p align="center"><img src="https://github.com/NNGU52/SpaceShip/blob/main/screenshots/4.%20%D0%94%D0%B2%D0%B8%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5%20%D0%BA%D0%BE%D1%81%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B3%D0%BE%20%D0%BA%D0%BE%D1%80%D0%B0%D0%B1%D0%BB%D1%8F%20%D0%BF%D1%80%D0%B8%20%D0%B2%D0%BA%D0%BB%D1%8E%D1%87%D0%B5%D0%BD%D0%B8%D0%B8%20%D1%82%D0%BE%D1%80%D0%BC%D0%BE%D0%B7%D0%BD%D0%BE%D0%B3%D0%BE%20%D0%B4%D0%B2%D0%B8%D0%B3%D0%B0%D1%82%D0%B5%D0%BB%D1%8F.png"/></p>
<p align="center"><img src="https://github.com/NNGU52/SpaceShip/blob/main/screenshots/5.%20%D0%94%D0%B2%D0%B8%D0%B6%D0%B5%D0%BD%D0%B8%D0%B8%20%D0%BA%D0%BE%D1%81%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B3%D0%BE%20%D0%BA%D0%BE%D1%80%D0%B0%D0%B1%D0%BB%D1%8F%20(%D1%81%20%D0%B4%D1%80%D1%83%D0%B3%D0%B8%D0%BC%D0%B8%20%D0%BD%D0%B0%D1%87%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%BC%D0%B8%20%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D0%BC%D0%B8)%20%D0%BF%D1%80%D0%B8%20%D0%B2%D0%BA%D0%BB%D1%8E%D1%87%D0%B5%D0%BD%D0%B8%D0%B8%20%D1%82%D0%BE%D1%80%D0%BC%D0%BE%D0%B7%D0%BD%D0%BE%D0%B3%D0%BE%20%D0%B4%D0%B2%D0%B8%D0%B3%D0%B0%D1%82%D0%B5%D0%BB%D1%8F.png"/></p>

В ходе проверки правильности работы программы требуется исследовать движение космического корабля на маленькой высоте над поверхностью Земли.
<p align="center"><img src="https://github.com/NNGU52/SpaceShip/blob/main/screenshots/6.%20%D0%9F%D0%B0%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5%20%D0%BA%D0%BE%D1%81%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B3%D0%BE%20%D0%BA%D0%BE%D1%80%D0%B0%D0%B1%D0%BB%D1%8F%20%D0%BD%D0%B0%20%D0%BF%D0%BE%D0%B2%D0%B5%D1%80%D1%85%D0%BD%D0%BE%D1%81%D1%82%D1%8C%20%D0%97%D0%B5%D0%BC%D0%BB%D0%B8%2C%20%D0%B2%D1%8B%D0%B7%D0%B2%D0%B0%D0%BD%D0%BD%D0%BE%D0%B5%20%D1%81%D0%BE%D0%BF%D1%80%D0%BE%D1%82%D0%B8%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5%D0%BC%20%D0%B0%D1%82%D0%BC%D0%BE%D1%81%D1%84%D0%B5%D1%80%D1%8B.png"/></p>

Далее был проделан опыт с космическим тело, приближающемся к Земле из бесконечности. Для этого в программе необходимо подкорректировать несколькозначений (начальное положение и коэффициенты для графиков энергий).
<p align="center"><img src="https://github.com/NNGU52/SpaceShip/blob/main/screenshots/7.%20%D0%94%D0%B2%D0%B8%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5%20%D0%BA%D0%BE%D1%81%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B3%D0%BE%20%D1%82%D0%B5%D0%BB%D0%B0%20%D0%B8%D0%B7%20%D0%B1%D0%B5%D1%81%D0%BA%D0%BE%D0%BD%D0%B5%D1%87%D0%BD%D0%BE%D1%81%D1%82%D0%B8%20%D1%81%20%D0%BF%D1%80%D0%B5%D0%B4%D0%B2%D0%B0%D1%80%D0%B8%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%20%D0%B7%D0%B0%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D0%BC%D0%B8%20%D0%BD%D0%B0%D1%87%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%BC%D0%B8%20%D0%BF%D0%B0%D1%80%D0%B0%D0%BC%D0%B5%D1%82%D1%80%D0%B0%D0%BC%D0%B8.png"/></p>

На данных примерах мы хорошо наблюдаем то, что при определенно подобранных прицельном параметре и начальной скорости, космическое тело падает на землю не более чем за один оборот, в иных случаях оно либо пролетает мимо планеты, либо приземляется, не сделав ни одного оборота.

### P.S.
Visual Studio 2013, MFC