USE [Northwind]
GO

-- 1.1 Построить запрос, формирующий вывод всех данных обо всех регионах
SELECT * FROM [dbo].[Region]
GO

-- 1.2 Построить запрос, формирующий вывод названия, адреса, города первых 5 поставщиков, отсортированные в алфавитном порядке по названию. 
SELECT TOP(5) [CompanyName], [Address], [City] 
FROM [dbo].[Suppliers] 
ORDER BY CompanyName
GO

-- 1.3 Вывести все данные о сотруднике Robert King
SELECT * FROM [dbo].[Employees]
WHERE ((LastName='Robert' AND FirstName='King') OR (LastName='King' AND FirstName='Robert'))
GO

-- 1.4 Вывести цены всех товаров, продажа которых прекращена (discontinued).
SELECT [ProductID], [ProductName], [UnitPrice] 
FROM [Northwind].[dbo].[Products]
WHERE Discontinued = 1
GO

-- 1.5 Сформировать список (содержащий наименование, отпускную цену, остаток) товаров на складе, остатки которых более 100 единиц.
SELECT [ProductName], [UnitPrice], [UnitsInStock] 
FROM [Northwind].[dbo].[Products]
WHERE UnitsInStock > 100
GO

-- 1.6. Вывести список всех сотрудников с днями рождения в октябре
SELECT * FROM [dbo].[Employees]
WHERE MONTH(BirthDate)=10
GO

-- 1.7. Определить, кто из сотрудников имеет степень Ph.D. (образование указано в столбце Notes)
SELECT * FROM [dbo].[Employees]
WHERE Notes LIKE '%Ph.D.%'
--((Notes LIKE '%Ph.%') AND (Notes LIKE '%D.%'))
GO

-- 1.8. Построить запрос, формирующий табличный вывод: фамилию сотрудника и указание старше он/она 60 лет или нет
SELECT LastName, 
		(SELECT
			CASE
				WHEN DATEDIFF(YEAR, BirthDate, GETDATE()) > 60 THEN 'Yes'
				WHEN DATEDIFF(YEAR, BirthDate, GETDATE()) <= 60 THEN 'No'
			END
		) as IsOlderThan60 FROM [dbo].[Employees]
GO


-- 2.1. Сформировать список (содержащий наименование, цену, остаток) товаров категории Beverages на складе, остатки которых более 100 единиц.
SELECT [ProductName], [UnitPrice], [UnitsInStock] 
FROM [dbo].[Products]
WHERE (UnitsInStock > 100 AND (SELECT CategoryName FROM [dbo].[Categories] WHERE [dbo].[Categories].CategoryID = [dbo].[Products].CategoryId) = 'Beverages')
GO

-- 2.2 Вывести общую стоимость всех заказов, которые оформил сотрудник фирмы “Steven Buchanan»  в июле 1996 г., с указанием кода заказа, даты заказа и общей суммы.
SELECT [OrderID], 
	   [OrderDate],
	   (SELECT SUM(UnitPrice * Quantity * (1 - Discount)) FROM [dbo].[Order Details] WHERE [dbo].[Orders].OrderID = [dbo].[Order Details].OrderID) as FullPrice 
		FROM [dbo].[Orders]
		WHERE ((SELECT EmployeeID FROM [dbo].[Employees] WHERE LastName = 'Buchanan' AND FirstName = 'Steven') = [dbo].[Orders].EmployeeID)
		AND (DATENAME(MM, OrderDate) = 'July' AND DATENAME(YYYY, OrderDate) = '1996')

-- SELECT SUM(UnitPrice * Quantity * (1 - Discount)) as FullPrice
-- FROM [dbo].[Order Details]
-- WHERE (OrderID IN
-- 	(SELECT [OrderID] FROM [dbo].[Orders]
-- 	WHERE ((SELECT EmployeeID FROM [dbo].[Employees]
-- 		WHERE LastName = 'Buchanan' AND FirstName = 'Steven') = [dbo].[Orders].EmployeeID)
-- 			AND (DATENAME(MM, OrderDate) = 'July' AND DATENAME(YYYY, OrderDate) = '1996')))
GO

-- 2.3 Вывести номера и даты заказов с товарами категории “Seafood”.
SELECT [OrderID], [OrderDate]
FROM [dbo].[Orders]
WHERE (OrderId IN (SELECT [OrderID] FROM [dbo].[Order Details]
		WHERE(ProductID IN (SELECT [ProductID] FROM [dbo].[Products]
			WHERE CategoryID = (SELECT [CategoryID] FROM [dbo].Categories WHERE CategoryName = 'Seafood')))))
GO

-- 2.4 Вывести все товары, отправленные в 1997 году в Канаду (неповторяющиеся значения) .
SELECT [ProductID], [ProductName] 
FROM [dbo].[Products]
WHERE ProductID IN (SELECT [ProductId] FROM [dbo].[Order Details]
	WHERE OrderID IN (SELECT [OrderId] FROM [dbo].[Orders] WHERE ShipCountry = 'Canada' AND DATENAME(YYYY, OrderDate) = '1997'))
GO

-- 2.5 Вывести все товары, отправленные в 1997 году в Канаду (неповторяющиеся значения) посредством Speedy Express.
SELECT [ProductID], [ProductName] FROM [dbo].[Products]
WHERE ProductID IN (SELECT [ProductId] FROM [dbo].[Order Details]
	WHERE OrderID IN (SELECT [OrderId] FROM [dbo].[Orders] WHERE ShipCountry = 'Canada' AND DATENAME(YYYY, OrderDate) = '1997'
						AND ShipVia = (SELECT [ShipperID] FROM [dbo].[Shippers] WHERE CompanyName = 'Speedy Express')))
GO


-- 3.1 Определить количество заказов в базе данных.
SELECT COUNT(OrderID) as TotalCount 
FROM [dbo].[Orders]
GO

-- 3.2 Выполнить расчет позиций и общую стоимость товаров, входящих в заказы, отправленные 21 октября 1997 года.
SELECT [ProductID]
      ,[ProductName]
	  ,(SELECT SUM(UnitPrice * Quantity * (1 - Discount)) AS TotalSum FROM [dbo].[Order Details]
			WHERE (OrderID IN (SELECT [OrderID] FROM [dbo].[Orders] 
						WHERE (DATENAME(YYYY, ShippedDate) = '1997' AND DATENAME(MM, ShippedDate) = 'October' AND DATENAME(DD, ShippedDate) = '21'))) 
			AND [dbo].[Products].ProductID = [dbo].[Order Details].ProductID)
  FROM [dbo].[Products]

SELECT SUM(UnitPrice * Quantity * (1 - Discount)) AS TotalSum 
FROM [dbo].[Order Details]
WHERE (OrderID IN (SELECT [OrderID] 
				   FROM [dbo].[Orders] 
				   WHERE (DATENAME(YYYY, ShippedDate) = '1997' AND DATENAME(MM, ShippedDate) = 'October' AND DATENAME(DD, ShippedDate) = '21')))
GO

-- 3.3 Выполнить расчет количества поставленного на склад товара с кодом 4 менеджером поставщика с кодом 3.
SELECT COUNT(UnitsInStock) As Quantity 
FROM [dbo].[Products]
WHERE (ProductID = 4) AND (SupplierID = 3)
GO

-- 3.4. Выполнить расчет общей стоимости поставленной продукции в феврале 1998 года 
SELECT SUM(UnitPrice * Quantity * (1 - Discount)) AS TotalSum 
FROM [dbo].[Order Details]
WHERE (OrderID IN (SELECT [OrderID] 
				   FROM [dbo].[Orders] 
				   WHERE (DATENAME(YYYY, ShippedDate) = '1998' AND DATENAME(MM, ShippedDate) = 'February')))
GO

-- 3.5. Получить количество типов товаров, продажи которых не прекращены
SELECT [CategoryID]
	  ,[CategoryName]
	  ,(SELECT COUNT(*) AS TotalCount
	  	FROM [dbo].[Products] 
		WHERE ([dbo].[Categories].CategoryID = [dbo].[Products].CategoryID) AND ([dbo].[Products].Discontinued = 0))
FROM [dbo].[Categories]

GO

-- 3.6. Выполнить расчет количества заказов, которые обслуживали сотрудники фирмы в 1997-1998 гг. с указанием года, сотрудника и количества заказов
SELECT [EmployeeID], DATENAME(YYYY, RequiredDate) as Year, COUNT(*) as Count
FROM [dbo].[Orders]
WHERE DATENAME(YYYY, RequiredDate) BETWEEN '1997' AND '1998'
GROUP BY [EmployeeID], DATENAME(YYYY, RequiredDate)
GO

-- 3.7. Вывести наименования категорий товаров на складе, остатки по которым меньше 100, с указанием категории и суммы остатка
SELECT [CategoryName],
	   (SELECT SUM(UnitsInStock) 
	   	FROM [dbo].[Products] 
		WHERE [dbo].[Categories].CategoryID = [dbo].[Products].CategoryID) AS TotalCount
FROM [dbo].[Categories]
WHERE ((SELECT SUM(UnitsInStock) 
		FROM [dbo].[Products] 
		WHERE [dbo].[Categories].CategoryID = [dbo].[Products].CategoryID) < 100)
GO

-- 3.9. Вывести список сотрудников, общая сумма заказов которых составила в 1996 г. 5000 и более денежных единиц
SELECT [EmployeeID]
      ,[LastName]
      ,[FirstName] 
FROM [dbo].[Employees]
WHERE ((SELECT SUM(UnitPrice * Quantity * (1 - Discount)) 
		FROM [dbo].[Order Details] 
		WHERE OrderID IN (SELECT [OrderID] 
						  FROM [dbo].[Orders] 
						  WHERE ([dbo].[Orders].EmployeeID = [dbo].[Employees].EmployeeID) AND (DATENAME(YYYY, [dbo].[Orders].RequiredDate) = '1996'))) 
		> 5000 )
GO

-- 3.10. Вывести стоимость заказов, отправленных в 1997 году, в разрезе стран.
SELECT A.ShipCountry, SUM(B.UnitPrice * B.Quantity * (1 - B.Discount))
FROM [dbo].[Orders] as A INNER JOIN [dbo].[Order Details] as B on A.OrderID = B.OrderID
WHERE DATENAME(YYYY, A.OrderDate) = '1997'
GROUP BY A.ShipCountry
GO

-- 3.11. Вывести стоимость заказов, отправленных в 1997 году, в разрезе стран, страны указаны в колонках итоговой таблицы.
SELECT A.ShipCountry, SUM(B.UnitPrice * B.Quantity * (1-B.Discount))
FROM [dbo].[Orders] as A INNER JOIN [dbo].[Order Details] as B on A.OrderID = B.OrderID
WHERE DATENAME(YYYY, A.OrderDate) = '1997'
GROUP BY A.ShipCountry
GO

-- 3.12 Вывести стоимость сделанных заказов помесячно с подведением промежуточных ежегодных итогов и общий итог.
SELECT SUM(UnitPrice * Quantity * (1 - Discount)) AS FullPrice 
FROM [dbo].[Order Details]

SELECT DATENAME(YYYY, A.OrderDate) AS Year, SUM(B.UnitPrice * B.Quantity * (1 - B.Discount)) AS AnualPrice
FROM [dbo].[Orders] as A INNER JOIN [dbo].[Order Details] as B on A.OrderID = B.OrderID
GROUP BY DATENAME(YYYY, A.OrderDate)
ORDER BY DATENAME(YYYY, A.OrderDate)

SELECT MONTH(A.OrderDate) AS Month, DATENAME(YYYY, A.OrderDate) AS Year, SUM(B.UnitPrice * B.Quantity * (1 - B.Discount)) AS MonthlyPrice
FROM [dbo].[Orders] as A INNER JOIN [dbo].[Order Details] as B on A.OrderID = B.OrderID
GROUP BY MONTH(A.OrderDate), DATENAME(YYYY, A.OrderDate)
ORDER BY DATENAME(YYYY, A.OrderDate) , MONTH(A.OrderDate)
GO

-- 3.13. Вывести стоимость всех заказов заказчика HILARION-Abastos в 1997 году помесячно. 
SELECT DATENAME(MM, A.OrderDate) as Month, SUM(B.UnitPrice * B.Quantity * (1-B.Discount)) as MonthlyPrice
FROM [dbo].[Orders] as A INNER JOIN [dbo].[Order Details] as B on A.OrderID = B.OrderID
WHERE DATENAME(YYYY, A.OrderDate) = '1997' AND A.CustomerID = (SELECT [CustomerID] 
															   FROM [dbo].Customers
															   WHERE [dbo].[Customers].ContactName = 'Hanna Moos')
GROUP BY DATENAME(MM, A.OrderDate)

-- 4.1. Вывести наименование товаров, остатки на складе которых от 5 до 10 и от 25 и более
SELECT [ProductName], [UnitsInStock] 
FROM [dbo].[Products]
WHERE (UnitsInStock BETWEEN 5 AND 10) OR (UnitsInStock > 25)
GO

-- 4.2. Вывести заказы, в которые включены более 2-х товаров
SELECT [OrderID], (SELECT COUNT(*) 
				   FROM [dbo].[Order Details] 
				   WHERE [dbo].[Orders].OrderID = [dbo].[Order Details].OrderID) as CountOfProducts
FROM [dbo].[Orders]
WHERE (SELECT COUNT(*) 
	   FROM [dbo].[Order Details] 
	   WHERE [dbo].[Orders].OrderID = [dbo].[Order Details].OrderID) > 2
GO

-- 4.3. Определить города, в которые направлены более 3 заказов
SELECT ShipCity, COUNT(*) as TotalCount
FROM [dbo].[Orders]
GROUP BY ShipCity
HAVING COUNT(*) > 3
GO


-- 5.1. Построить запрос для определения изменения средней стоимости заказа в ноябре 1997 г по сравнению с ноябрём 1996 г.
DECLARE @PriceNovember1997 INT
DECLARE @PriceNovember1996 INT
DECLARE @CountNovember1997 INT
DECLARE @CountNovember1996 INT

SET @PriceNovember1997 = (SELECT SUM(UnitPrice * Quantity * (1 - Discount)) 
						  FROM [dbo].[Order Details] 
						  WHERE [dbo].[Order Details].OrderID IN (SELECT [OrderID] 
							  									  FROM [dbo].[Orders]
																  WHERE DATENAME(YYYY, [dbo].[Orders].OrderDate) = '1997' AND DATENAME(MM, [dbo].[Orders].OrderDate) = 'NOVEMBER'))

																				  
SET @PriceNovember1996 = (SELECT SUM(UnitPrice * Quantity * (1 - Discount)) 
						  FROM [dbo].[Order Details] 
						  WHERE [dbo].[Order Details].OrderID IN (SELECT [OrderID] 
							  									  FROM [dbo].[Orders]
																  WHERE DATENAME(YYYY, [dbo].[Orders].OrderDate) = '1996' AND DATENAME(MM, [dbo].[Orders].OrderDate) = 'NOVEMBER'))

SET @CountNovember1997 = (SELECT Count(*) 
						  FROM [dbo].[Orders] 
						  WHERE DATENAME(YYYY, [dbo].[Orders].OrderDate) = '1997' AND DATENAME(MM, [dbo].[Orders].OrderDate) = 'NOVEMBER')

SET @CountNovember1996 = (SELECT Count(*) 
						  FROM [dbo].[Orders] 
						  WHERE DATENAME(YYYY, [dbo].[Orders].OrderDate) = '1996' AND DATENAME(MM, [dbo].[Orders].OrderDate) = 'NOVEMBER')


SELECT (@PriceNovember1997 / @CountNovember1997) - (@PriceNovember1996 / @CountNovember1996) as PriceDifference
GO


-- 5.2. Построить запрос для определения среднего и медианного значений стоимости заказов в 1997 году
DECLARE @ResultOrders TABLE(RowNumber INT, TotalSum MONEY);
INSERT INTO @ResultOrders
	SELECT ROW_NUMBER() OVER(ORDER BY SUM(ExtendedPrice)) AS RowNumber, 
		   SUM(ExtendedPrice) AS TotalSum
	FROM Orders AS Main
	INNER JOIN [Order Details Extended] AS Details ON Details.OrderID = Main.OrderID
	WHERE YEAR(OrderDate)=1997
	GROUP BY Main.OrderID
	ORDER BY SUM(ExtendedPrice);

SELECT AVG(TotalSum) AS AveragePrice
FROM @ResultOrders;

SELECT TotalSum AS MedianPrice
FROM @ResultOrders
WHERE RowNumber=(SELECT (COUNT(*) + 1) / 2
				 FROM @ResultOrders)