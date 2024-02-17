--Внеси в скрипт part3.sql создание ролей и выдачу им прав в соответствии с описанным ниже.
--Администратор
--Администратор имеет полные права на редактирование и просмотр любой информации, запуск и остановку процесса обработки.
--Посетитель
--Только просмотр информации из всех таблиц.

--DROP OWNED BY visitor;
DROP ROLE IF EXISTS visitor;

--https://postgrespro.ru/docs/postgresql/14/sql-createrole?lang=ru-en
CREATE ROLE visitor WITH LOGIN NOSUPERUSER NOCREATEDB NOCREATEROLE;

GRANT CONNECT ON DATABASE postgres TO visitor;
GRANT USAGE ON SCHEMA public TO visitor;
--https://postgrespro.ru/docs/postgrespro/10/sql-grant#:~:text=%D0%94%D0%BB%D1%8F%20%D1%81%D1%85%D0%B5%D0%BC%20%D1%8D%D1%82%D0%BE%20%D0%BF%D1%80%D0%B0%D0%B2%D0%BE%20%D0%B4%D0%B0%D1%91%D1%82,%D0%BD%D0%B0%D0%B4%D1%91%D0%B6%D0%BD%D0%BE%20%D0%BF%D0%B5%D1%80%D0%B5%D0%BA%D1%80%D1%8B%D1%82%D1%8C%20%D0%B4%D0%BE%D1%81%D1%82%D1%83%D0%BF%20%D0%BA%20%D0%BE%D0%B1%D1%8A%D0%B5%D0%BA%D1%82%D0%B0%D0%BC.
GRANT SELECT ON ALL TABLES IN SCHEMA public TO visitor;
GRANT SELECT ON ALL SEQUENCES IN SCHEMA public TO visitor;
ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT SELECT ON TABLES TO visitor;

--https://postgrespro.ru/docs/postgrespro/10/sql-revoke
REVOKE CREATE ON SCHEMA public FROM PUBLIC;

--DROP OWNED BY administrator;
DROP ROLE IF EXISTS administrator;
CREATE ROLE administrator WITH LOGIN SUPERUSER;
SELECT * FROM pg_roles where left(rolname, 2) <> 'pg';
