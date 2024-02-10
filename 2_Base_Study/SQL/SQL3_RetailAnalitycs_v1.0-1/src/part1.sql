-- personal_data
DROP TABLE IF EXISTS personal_data Cascade;
CREATE TABLE IF NOT EXISTS personal_data (
    Customer_id SERIAL PRIMARY KEY,
    Customer_Name VARCHAR NOT NULL CHECK(Customer_Name ~ '^([А-Я]{1}[а-яё\- ]{0,}|[A-Z]{1}[a-z\- ]{0,})$'),
    Customer_Surname VARCHAR NOT NULL CHECK (Customer_Surname ~ '^([А-Я]{1}[а-яё\- ]{0,}|[A-Z]{1}[a-z\- ]{0,})$'),
    Customer_Primary_Email VARCHAR NOT NULL UNIQUE CHECK (Customer_Primary_Email ~ '^[A-Za-z0-9._+%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$'),
    Customer_Primary_Phone VARCHAR NOT NULL UNIQUE CHECK (Customer_Primary_Phone ~ '^[+]7[0-9]{10}$')
);

--cards
DROP TABLE IF EXISTS cards CASCADE;
CREATE TABLE IF NOT EXISTS cards (
    Customer_Card_Id SERIAL PRIMARY KEY,
    Customer_Id INT REFERENCES personal_data(Customer_Id) ON UPDATE CASCADE ON DELETE CASCADE
);
COMMENT ON COLUMN cards.Customer_ID IS 'One customer several cards';


--transactions
DROP TABLE IF EXISTS transactions CASCADE;
CREATE TABLE transactions (
    Transaction_ID SERIAL PRIMARY KEY,
    Customer_Card_ID INT NOT NULL,
    Transaction_Summ NUMERIC NOT NULL,
    Transaction_DateTime TIMESTAMP NOT NULL,
    Transaction_Store_ID INT NOT NULL,
    FOREIGN KEY (Customer_Card_ID) REFERENCES cards (Customer_Card_ID)
);

COMMENT ON COLUMN transactions.Transaction_ID IS 'uniq';
COMMENT ON COLUMN transactions.Transaction_Summ IS 'transaction sum in rubles(full purchase price excluding discounts)';
COMMENT ON COLUMN transactions.Transaction_DateTime IS 'transaction date and time';
COMMENT ON COLUMN transactions.Transaction_Store_ID IS 'store of transaction';

-- sku groups
DROP TABLE IF EXISTS sku_groups CASCADE;

CREATE TABLE IF NOT EXISTS sku_groups (
    Group_Id SERIAL PRIMARY KEY, 
    Group_Name VARCHAR NOT NULL UNIQUE CHECK (Group_Name ~ '^[[:print:]]*$') 
);

-- goods_grid
DROP TABLE IF EXISTS goods_grid CASCADE;

CREATE TABLE IF NOT EXISTS goods_grid (
    Sku_Id SERIAL PRIMARY KEY, 
    Sku_Name VARCHAR NOT NULL CHECK (Sku_Name ~ '^[[:print:]]*$'), 
    Group_Id INT REFERENCES sku_groups (Group_Id) ON UPDATE CASCADE ON DELETE CASCADE
);


-- checks
DROP TABLE IF EXISTS checks CASCADE;

CREATE TABLE IF NOT EXISTS checks (
    Transaction_Id INT REFERENCES transactions (Transaction_Id) ON UPDATE CASCADE ON DELETE CASCADE, 
    Sku_Id INT REFERENCES goods_grid (Sku_Id) ON UPDATE CASCADE ON DELETE CASCADE, 
    Sku_Amount NUMERIC NOT NULL CHECK (Sku_Amount >= 0), 
    Sku_Summ NUMERIC NOT NULL CHECK (Sku_Summ >= 0), 
    Sku_Summ_Paid NUMERIC NOT NULL CHECK (Sku_Summ_Paid >= 0), 
    Sku_Discount NUMERIC NOT NULL CHECK (Sku_Discount >= 0)
);

COMMENT ON COLUMN checks.Transaction_ID IS 'For all products in the check';

COMMENT ON COLUMN checks.SKU_Amount IS 'Quantity of the purchased product';

COMMENT ON COLUMN checks.SKU_Summ IS 'The purchase sum (without discounts and bonuses)';

COMMENT ON COLUMN checks.SKU_Summ_Paid IS 'paid for the product not including the discount';

COMMENT ON COLUMN checks.SKU_Discount IS 'discount value in rubles';

-- stores
DROP TABLE IF EXISTS stores CASCADE;

CREATE TABLE IF NOT EXISTS stores (
    Transaction_Store_Id INT,
    Sku_Id BIGINT REFERENCES goods_grid (Sku_Id) ON UPDATE CASCADE ON DELETE CASCADE, 
    Sku_Purchase_Price NUMERIC NOT NULL CHECK (Sku_Purchase_Price >= 0), 
    Sku_Retail_Price NUMERIC NOT NULL CHECK (Sku_Retail_Price >= 0)
);

COMMENT ON COLUMN stores.SKU_Purchase_Price IS 'Purchasing price of products';
COMMENT ON COLUMN stores.SKU_Retail_Price IS 'The sale price of the product without discounts';

-- analysis_form_date
DROP TABLE IF EXISTS analysis_form_date CASCADE;

CREATE TABLE IF NOT EXISTS analysis_form_date (
    Analysis_Formation TIMESTAMP
);

SET DATESTYLE to iso, DMY;

-- IMPORT
SET import_dir.const TO '/tmp/retail/import/';
DROP PROCEDURE IF EXISTS import_from_file;
CREATE OR REPLACE PROCEDURE import_from_file(
    IN table_name VARCHAR, 
    IN file_name VARCHAR, 
    IN delimiter VARCHAR DEFAULT 'E''\t''') AS 
$$
BEGIN
	EXECUTE format('COPY %s FROM %L WITH DELIMITER %s', $1, current_setting('import_dir.const') || $2, $3);
END;
$$ LANGUAGE plpgsql; 
CALL import_from_file ('personal_data', 'Personal_Data_Mini.tsv');
CALL import_from_file ('cards', 'Cards_Mini.tsv');
CALL import_from_file ( 'transactions', 'Transactions_Mini.tsv' );
CALL import_from_file ( 'sku_groups', 'Groups_SKU_Mini.tsv' );
CALL import_from_file ( 'goods_grid', 'SKU_Mini.tsv' );
CALL import_from_file ('checks', 'Checks_Mini.tsv');
CALL import_from_file ('stores', 'Stores_Mini.tsv');
CALL import_from_file ('analysis_form_date', 'Date_Of_Analysis_Formation.tsv');


-- EXPORT
SET export_dir.const TO '/tmp/retail/export/';
DROP PROCEDURE IF EXISTS export_to_file;

CREATE OR REPLACE PROCEDURE export_to_file (
    IN table_name VARCHAR, 
    IN file_name VARCHAR, 
    IN delimeter VARCHAR DEFAULT 'E''\t''') AS 
$$
BEGIN
	EXECUTE format('COPY %s TO %L WITH DELIMITER %s', $1, current_setting('export_dir.const') || $2, $3);
END;
$$ LANGUAGE plpgsql; 

CALL export_to_file ('personal_data', 'Personal_Data_Mini.tsv');
CALL export_to_file ('cards', 'Cards_Mini.tsv');
CALL export_to_file ( 'transactions', 'Transactions_Mini.tsv' );
CALL export_to_file ( 'sku_groups', 'Groups_SKU_Mini.tsv' );
CALL export_to_file ( 'goods_grid', 'SKU_Mini.tsv' );
CALL export_to_file ('checks', 'Checks_Mini.tsv');
CALL export_to_file ('stores', 'Stores_Mini.tsv');
CALL export_to_file ('analysis_form_date', 'Date_Of_Analysis_Formation.tsv');
