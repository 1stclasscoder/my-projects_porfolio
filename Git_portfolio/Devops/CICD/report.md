# Basic CI/CD

### Part 1. Настройка **gitlab-runner**

##### Подними виртуальную машину *Ubuntu Server 22.04 LTS*.
*Будь готов, что в конце проекта нужно будет сохранить дамп образа виртуальной машины.*
![virtual box](images/1.1.png) <br>

##### Скачай и установи на виртуальную машину **gitlab-runner**.

##### 1. Загрузка бинарного файла:
sudo curl -L --output /usr/local/bin/gitlab-runner "https://s3.dualstack.us-east-1.amazonaws.com/gitlab-runner-downloads/latest/binaries/gitlab-runner-linux-amd64"
![load file](images/1.2.png) <br>

##### 2. Передача файлу разрешения на исполнение: sudo chmod +x /usr/local/bin/gitlab-runner
![send](images/1.3.png) <br>

##### 3. Создать пользователя GitLab CI: sudo useradd --comment 'GitLab Runner' --create-home gitlab-runner --shell /bin/bash
![create user](images/1.4.png) <br>

##### 4. Установить службой: sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner
![set directory](images/1.5.png) <br>

##### 5. Запуск: sudo gitlab-runner start
![use](images/1.6.png) <br>

##### 6. Проверка запуска: systemctl status gitlab-runner.service
![check](images/1.7.png) <br>

##### Запуск **gitlab-runner** и регистрирация для использования проекте (*DO6_CICD*).
![use gitlab](images/1.8.png) <br>
![use gitlab](images/1.9.png) <br>
![use gitlab](images/1.10.png) <br>

### Part 2. Сборка

##### В файле _gitlab-ci.yml_ добавил этап запуска сборки через мейк файл из проекта _C2_ с созранением файлов со сроком хранения 30 дней..
![use gitlab](images/2.1.png) <br>
![use gitlab](images/2.2.png) <br>

##### Ошибка при запуске в гитлабе по причине очистки терминала при выходе из оболочки shell.
![use gitlab](images/2.3.png) <br>

##### Комментирование строк в конфигурационном файле решает данную проблему, так как они очищают терминал при выходе из оболочки shell.
![comment](images/2.4.png) <br>

##### Повторный запуск проекта.
![use](images/2.5.png) <br>

##### Сборка прошла успешно.
![use](images/2.6.png) <br>


### Part 3. Тест кодстайла

#### Этап для **CI**, который запускает скрипт кодстайла (*clang-format*).
![code-style](images/3.1.png) <br>

#### Проверка code-style на локальной машине.
![local code-style](images/3.2.png) <br>

#### Проверка code-style на git-runner.
![code-style](images/3.3.png) <br>
![code-style](images/3.4.png) <br>
#### Исправление ошибок code-style.
![change file](images/3.5.png) <br>

#### Проверка code-style на локальной машине.
![local code-style2](images/3.6.png) <br>

#### Проверка code-style на git-runner.
![code-style2](images/3.7.png) <br>

#### Проект проходит успешную проверку на code-style на git-runner.
![code-style2](images/3.8.png) <br>

### Part 4. Интеграционные тесты

#### Написание этапа для **CI**, который запускает интеграционные тесты из того же проекта.
![use](images/4.1.png) <br>

#### Проверка фейла тестов на локальной машине.
![check](images/4.2.png) <br>

#### Проверка тестов на git-runner.
![check-tests](images/4.3.png) <br>
![check-tests](images/4.4.png) <br>

#### Проверка тестов после исправления ошибки на локальной машине.
![check-tests](images/4.5.png) <br>

#### Проверка тестов на git-runner после исправления ошибки.
![check-tests](images/4.6.png) <br>
![check-tests](images/4.7.png) <br>

### Part 5. Этап деплоя

##### Поднятие второй виртуальной машины *Ubuntu Server 22.04 LTS*.
![turn on](images/5.1.png) <br>

##### Настройка внутренних сетей (прописание статических путей).
![ways](images/5.2.png) <br>

##### Создание SSH ключа на второй машине и добавление его в gitlab.
![create](images/5.3.png) <br>
![use](images/5.4.png) <br>

##### Написание скрипта на стадии deploy.
![script](images/5.5.png) <br>

##### Изменение настроек ранера для обозначения пути поиска ssh агента.
![script](images/5.6.png) <br>

##### Сохраняем отпечаток удаленного сервера в папке ранера .ssh/known_hosts.
![set host](images/5.7.png) <br>

##### Добавляем файл ключа ssh в папку .ssh внутри ранера.
![add](images/5.8.png) <br>

##### Изменяем разрешения файлов для использования ранером.
![dir](images/5.9.png) <br>

##### Копируем содержимое ssh ключа на удаленный сервер.
![change](images/5.10.png) <br>

##### Даем разрешение на перемещение файлов внутри второй машины.
![change](images/5.11.png) <br>

##### Проверяем работу стадии deploy внутри gitlab-runner.
![change](images/5.12.png) <br>

### Part 6. Дополнительно. Уведомления

##### Настрой уведомления о успешном/неуспешном выполнении пайплайна через бота с именем «[твой nickname] DO6 CI/CD» в *Telegram*.

##### Через телеграм бота создаем отдельного бота, которого будем использовать и получаем его токен.
![bot](images/6.1.png) <br>

##### Через другого телеграм бота получаем id.
![bot](images/6.2.png) <br>

##### Добавляем скрипт по направлению сообщений в after-script.
![after-script](images/6.3.png) <br>
![after-script](images/6.4.png) <br>
![after-script](images/6.5.png) <br>
![after-script](images/6.6.png) <br>

##### Пишем скрипт по отправке сообщений.
![script](images/6.7.png) <br>

##### Бот работает.
![script](images/6.8.png) <br>