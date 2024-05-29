# Фоторедактор 

## Цель и описание

Целью данного проекта является создание полнофункционального фоторедактора на языке программирования C++. Эта работа представляет собой инструмент для эффективного редактирования цифровых изображений.

<img src="images_for_md/1.png" width="800" height="400">

### Пользовательское описание

#### Основные функции

- После запуска приложения нажмите `CTRL+O` или выберите `file -> open`, чтобы открыть проводник.

<img src="images_for_md/3.png" width="600" height="400">

- Выберите изображение в формате `.jpg` для редактирования.
  
<img src="images_for_md/4.png" width="600" height="300">

- Нажмите `CTRL+P` для открытия ползунков или `CTRL+T` для открытия текстовых полей для изменения параметров изображения. Также можно нажать на кнопку `settings` и выбрать `text parameters` или `sliders parameters`.

<img src="images_for_md/7.png" width="600" height="300">

<img src="images_for_md/8.png" width="600" height="300">

- В случае необходимости нажмите `CTRL+L` для сброса значений по умолчанию или выберите `settings -> default parameters`.

<img src="images_for_md/5.png" width="600" height="300">

<img src="images_for_md/6.png" width="600" height="300">

- Сохраните измененное изображение, нажав `CTRL+S` или выбрав `file -> save`.

<img src="images_for_md/9.png" width="600" height="300">

- Чтобы закрыть приложение, можете нажать `CTRL+W` или `file->close`. Вам высветиться уведомление, в котором будет предложено сохранить изображение, закрыть уведомление или выйти из приложения.

<img src="images_for_md/11.png" width="600" height="300">

-	Далее вы можете зайти в проводник и открыть сохранённое изображение

<img src="images_for_md/13.png" width="600" height="200">

<img src="images_for_md/12.png" width="600" height="300">

### Пользовательская документация

#### Общая информация

Функционал приложения реализован в файле `photo_editors.cpp` с использованием класса `ScanGui`. Разработка осуществлена на C++ с графическим интерфейсом пользователя.

#### Принцип работы приложения

- **Запуск приложения**: Создание окна с помощью библиотеки GLFW, настройка его размера и вида, интеграция библиотек Dear ImGui с OpenGL и GLFW.
- **Графический интерфейс**: Реализация интерфейса с использованием ImGui и OpenCV.
- **Обработка изображений**: Открытие изображения, его обработка с помощью методов OpenCV, создание текстуры и вывод в GUI.
- **Горячие клавиши**: Реализация реакции на комбинации клавиш с помощью метода `KeysDown[]` из Dear ImGui.

### Инструкция по установке и запуску

1. Скачайте проект с помощью Git:
git clone https://GITHUB.COM/AKNYAZP/MISIS2023F-22-04-KNYAZEV-A-P.GIT

2. Перейдите в директорию проекта:
cd path/to/project/misis2023f-22-04-knyazev-a-p

3. Соберите проект:
mkdir build && cd build cmake -DCMAKE_TOOLCHAIN_FILE="path/to/vcpkg/scripts/buildsystems/vcpkg.cmake".. cmake --build. --config Release

4. Запустите приложение:
cd../bin.rel photo_editors.exe


### Техническая документация

#### Editor

Класс `Editor` управляет графическим интерфейсом и рендерингом окна ImGui.

#### Image

Класс `Image` обеспечивает работу с изображениями, включая обработку и отображение.

### Список использованных источников

- Официальная документация Dear ImGui: [Dear ImGui](https://github.com/ocornut/imgui/blob/master/docs/README.md)
- ImGuiFileDialog: [ImGuiFileDialog](https://github.com/aiekick/ImGuiFileDialog)
- Примеры загрузки и отображения изображений ImGui: [ImGui Image Loading and Displaying Examples](https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples)
- Документация по использованию Doxygen: [Doxygen](https://habr.com/ru/articles/252101/)
- Документация по использованию OpenCV: [OpenCV](https://docs.opencv.org/4.x/d1/dfb/intro.html)
- Документация по использованию OpenGL: [OpenGL](https://docs.gl/)
