# Web
## How to run project:
**Run:** $ git clone https://github.com/Stanislav-3/Web && cd Web && docker-compose up --build

## Testing
Использована среда тестирования **pytest**, в случае форм также использован класс **TestCase**. Использованы *fixtures* и *parametrize*
<img width="394" alt="web_tests" src="https://user-images.githubusercontent.com/61240903/121125281-fa666f00-c82e-11eb-8212-6606cb37ac1f.png">

## Other requirements
1) Реализован механизм **авторизации/аутентификации** (login as client). После авторизации доступен профиль клиента.
2) Добавлено **логирование** *(уровень логирования берется из shop/my_config.py)*.
3) Реализованы связи **one-to-one** *(main.Profile-settings.AUTH_USER_MODEL)*, **one-to-many** *(main.Category-main.Product)* и др.,
   **many-to-many** *(main.ProductReward-main.Product)*.
4) **Join** запросы реализованы с помощью select_related *(orders.views.order_specific и др.)*.
5) Валидация **форм** происходит на стороне сервера и клиента.
6) Используя фреймворк **VanillaJS** написан таймер in Footer.
7) Использован **css**.
8) Использован **multithreading** *(main.views.get_login_page и др.)*.
9) Разработан **Dockerfile** и **docker-compose**, использующий автоматически билдящийся образ stanislav3/web-app
   *(https://hub.docker.com/repository/docker/stanislav3/web-app)*.
