USE [University]
GO

-- 1. Добавить  факультеты КСИС и ФИТУ
INSERT INTO [dbo].[FACULTY]
           ([ID]
           ,[NAME])
     VALUES
           (NEWID()
           ,'FKSIS')
GO

INSERT INTO [dbo].[FACULTY]
           ([ID]
           ,[NAME])
     VALUES
           (NEWID()
           ,'FITU')
GO


-- 2. Добавить новую группу с номером 123456. Внести в групп 123456 студентов Иванова и Петрова. Назначить студента Иванова старостой группы

-- Создание группы
INSERT INTO [dbo].[GROUPS]
           ([ID]
           ,[NAME]
           ,[HEAD_GROUP]
           ,[FACULTY_ID])
     VALUES
           (NEWID()
           ,'123456'
           ,NULL
           ,(SELECT ID FROM FACULTY WHERE NAME='FKSIS')
)
GO

-- Создание студентов и внесение их в группу 123456
INSERT INTO [dbo].[STUDENTS]
           ([ID]
           ,[LAST_NAME]
           ,[FIRST_NAME]
           ,[GROUP_ID])
     VALUES
           (NEWID()
           ,'Ivanov'
           ,NULL
           ,(SELECT ID FROM GROUPS WHERE NAME='123456'))
GO

INSERT INTO [dbo].[STUDENTS]
           ([ID]
           ,[LAST_NAME]
           ,[FIRST_NAME]
           ,[GROUP_ID])
     VALUES
           (NEWID()
           ,'Petrov'
           ,NULL
           ,(SELECT ID FROM GROUPS WHERE NAME='123456'))
GO

-- Назначение студента Иванова старостой группы
UPDATE [dbo].[GROUPS]
   SET [HEAD_GROUP] = (SELECT ID FROM STUDENTS WHERE LAST_NAME='Ivanov')
 WHERE NAME = '123456'
GO


-- 3. Добавить преподавателей Васечкина и Петечкина на факультеты КСИС и ФИТУ соответственно
INSERT INTO [dbo].[PREPODS]
           ([ID]
           ,[LAST_NAME]
           ,[FIRST_NAME]
           ,[FACULTY_ID])
     VALUES
           (NEWID()
           ,'Vasechkin'
           ,NULL
           ,(SELECT ID FROM FACULTY WHERE NAME='FKSIS'))
GO

INSERT INTO [dbo].[PREPODS]
           ([ID]
           ,[LAST_NAME]
           ,[FIRST_NAME]
           ,[FACULTY_ID])
     VALUES
           (NEWID()
           ,'Petechkin'
           ,NULL
           ,(SELECT ID FROM FACULTY WHERE NAME='Fitu'))
GO


-- 4. Назначить преподавателю Васечкину ведение предмета «Введение в специальность» для группы 123456. Проверить планы выполнения запроса Actual и Eastimated 

-- Создание предмета «Введение в специальность»
INSERT INTO [dbo].[SUBJECTS]
		   ([ID]
		   ,[NAME]
		   ,[FACULTY_ID])
	 VALUES
		   (NEWID()
		   ,'Vvedenie v specialnost'
		   ,(SELECT FACULTY_ID FROM PREPODS WHERE LAST_NAME='Vasechkin'))
GO

-- Создание type_stydy_load
INSERT INTO [dbo].[TYPE_STUDY_LOAD]
       ([ID]
       ,[NAME])
 VALUES
       (NEWID()
       ,'Lection')
GO

-- Создание study_load
INSERT INTO [dbo].[STUDY_LOAD]
       ([ID]
       ,[hours]
       ,[SUBJECT_ID]
       ,[Type_STYDY_ID])
 VALUES
       ('Lection'
       ,NULL
       ,(SELECT ID FROM SUBJECTS WHERE NAME='Vvedenie v specialnost')
       ,(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='Lection'))
GO

-- Создание lesson
INSERT INTO [dbo].[LESSONS]
       ([GROUP_ID]
       ,[PREPOD_ID]
       ,[STUDY_ID])
 VALUES
       ((SELECT ID FROM GROUPS WHERE NAME='123456')
       ,(SELECT ID FROM PREPODS WHERE LAST_NAME='Vasechkin')
       ,(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM SUBJECTS WHERE NAME='Vvedenie v specialnost')))
GO
	

-- 5. Поставить Студенту Иванову по предмету «Введение в специальность» оценку 10, отметить отсутствие студента Петрова на данном занятии
INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,10
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Ivanov')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Vasechkin')
           ,'NO')


-- 6. Наполнить базу таким образом, чтобы в базе появилась информация по различным предметам (минимум 4), по каждому из которых стояло бы не менее 3 отметок(минимум 5 студентам ). По как минимум двум запросам вывести статистику выполнения;
	
-- Создание студентов. 
INSERT INTO [dbo].[STUDENTS]
           ([ID]
           ,[LAST_NAME]
           ,[FIRST_NAME]
           ,[GROUP_ID])
     VALUES
           (NEWID()
           ,'Sidorov'
           ,'Sidr'
           ,(SELECT ID FROM GROUPS WHERE NAME='123456'))
		   

INSERT INTO [dbo].[STUDENTS]
           ([ID]
           ,[LAST_NAME]
           ,[FIRST_NAME]
           ,[GROUP_ID])
     VALUES
           (NEWID()
           ,'Pirozkov'
           ,'Pirog'
           ,(SELECT ID FROM GROUPS WHERE NAME='123456'))
	   
INSERT INTO [dbo].[STUDENTS]
           ([ID]
           ,[LAST_NAME]
           ,[FIRST_NAME]
           ,[GROUP_ID])
     VALUES
           (NEWID()
           ,'Bulochkin'
           ,'Semen'
           ,(SELECT ID FROM GROUPS WHERE NAME='123456'))

-- Создание предметов.
-- Предмет 1
INSERT INTO [dbo].[SUBJECTS]
		   ([ID]
		   ,[NAME]
		   ,[FACULTY_ID])
	 VALUES
		   (NEWID()
		   ,'MMA'
		   ,(SELECT FACULTY_ID FROM PREPODS WHERE LAST_NAME='Vasechkin'))
GO

INSERT INTO [dbo].[STUDY_LOAD]
       ([ID]
       ,[hours]
       ,[SUBJECT_ID]
       ,[Type_STYDY_ID])
 VALUES
       ('Lection2'
       ,NULL
       ,(SELECT ID FROM SUBJECTS WHERE NAME='MMA')
       ,(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='Lection'))
GO

INSERT INTO [dbo].[LESSONS]
       ([GROUP_ID]
       ,[PREPOD_ID]
       ,[STUDY_ID])
 VALUES
       ((SELECT ID FROM GROUPS WHERE NAME='123456')
       ,(SELECT ID FROM PREPODS WHERE LAST_NAME='Vasechkin')
       ,(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM SUBJECTS WHERE NAME='MMA')))
GO

-- Предмет 2
INSERT INTO [dbo].[SUBJECTS]
		   ([ID]
		   ,[NAME]
		   ,[FACULTY_ID])
	 VALUES
		   (NEWID()
		   ,'MCHA'
		   ,(SELECT FACULTY_ID FROM PREPODS WHERE LAST_NAME='Petechkin'))
GO

INSERT INTO [dbo].[STUDY_LOAD]
       ([ID]
       ,[hours]
       ,[SUBJECT_ID]
       ,[Type_STYDY_ID])
 VALUES
       ('Lection3'
       ,NULL
       ,(SELECT ID FROM SUBJECTS WHERE NAME='MCHA')
       ,(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='Lection'))
GO

INSERT INTO [dbo].[LESSONS]
       ([GROUP_ID]
       ,[PREPOD_ID]
       ,[STUDY_ID])
 VALUES
       ((SELECT ID FROM GROUPS WHERE NAME='123456')
       ,(SELECT ID FROM PREPODS WHERE LAST_NAME='Petechkin')
       ,(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM SUBJECTS WHERE NAME='MCHA')))
GO

-- Предмет 3
INSERT INTO [dbo].[SUBJECTS]
		   ([ID]
		   ,[NAME]
		   ,[FACULTY_ID])
	 VALUES
		   (NEWID()
		   ,'MGIA'
		   ,(SELECT FACULTY_ID FROM PREPODS WHERE LAST_NAME='Petechkin'))
GO

INSERT INTO [dbo].[STUDY_LOAD]
       ([ID]
       ,[hours]
       ,[SUBJECT_ID]
       ,[Type_STYDY_ID])
 VALUES
       ('Lection4'
       ,NULL
       ,(SELECT ID FROM SUBJECTS WHERE NAME='MGIA')
       ,(SELECT ID FROM TYPE_STUDY_LOAD WHERE NAME='Lection'))
GO

INSERT INTO [dbo].[LESSONS]
       ([GROUP_ID]
       ,[PREPOD_ID]
       ,[STUDY_ID])
 VALUES
       ((SELECT ID FROM GROUPS WHERE NAME='123456')
       ,(SELECT ID FROM PREPODS WHERE LAST_NAME='Petechkin')
       ,(SELECT ID FROM STUDY_LOAD WHERE SUBJECT_ID=(SELECT ID FROM SUBJECTS WHERE NAME='MGIA')))
GO

-- Назначение оценок
-- Предмет МГИА
INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,8
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Petrov')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection4')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Petechkin')
           ,'YES')
GO

INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,7
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Bulochkin')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection4')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Petechkin')
           ,'YES')
GO

INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,10
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Bulochkin')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection4')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Petechkin')
           ,'YES')
GO

-- Предмет МЧА
INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,6
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Sidorov')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection3')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Petechkin')
           ,'NO')
GO

INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,9
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Pirozkov')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection3')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Petechkin')
           ,'YES')
GO

INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,7
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Ivanov')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection3')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Petechkin')
           ,'NO')
GO

-- Предмет ММА
INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,8
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Bulochkin')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection2')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Vasechkin')
           ,'YES')
GO

INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,9
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Ivanov')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection2')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Vasechkin')
           ,'YES')
GO

INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,10
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Petrov')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection2')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Vasechkin')
           ,'YES')
GO

-- Предмет Введение в специальность
INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,7
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Bulochkin')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Vasechkin')
           ,'NO')

INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,9
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Sidorov')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Vasechkin')
		   ,'YES')

INSERT INTO [dbo].[RAITING]
           ([ID]
           ,[DATE]
           ,[VAL]
           ,[STUDENT_ID]
           ,[STUDY_ID]
           ,[PREPODS_ID]
           ,[IS_ABSENT])
     VALUES
           (NEWID()
           ,GETDATE()
           ,8
           ,(SELECT ID FROM STUDENTS WHERE LAST_NAME = 'Pirozkov')
           ,(SELECT ID FROM STUDY_LOAD WHERE ID = 'Lection')
           ,(SELECT ID FROM PREPODS WHERE LAST_NAME = 'Vasechkin')
		   ,'YES')


-- 7. Cоздаём файловую группу

ALTER DATABASE University
ADD FILEGROUP fileGroup
GO

ALTER DATABASE University
ADD FILE
(
	NAME = testFile,
	FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL15.SQLEXPRESS\MSSQL\DATA\testfile.ndf',
	SIZE = 5MB,
    MAXSIZE = 100MB,
    FILEGROWTH = 5MB
)
TO FILEGROUP fileGroup
GO


--7. скрипты удаления
DELETE FROM [dbo].[RAITING]
DELETE FROM [dbo].[LESSONS]
DELETE FROM [dbo].[STUDY_LOAD]
DELETE FROM [dbo].[TYPE_STUDY_LOAD]
DELETE FROM [dbo].[SUBJECTS]
DELETE FROM [dbo].[PREPODS]

UPDATE [dbo].[GROUPS]
   SET [HEAD_GROUP] = NULL
 WHERE NAME = '123456'
 
DELETE FROM [dbo].[STUDENTS]
DELETE FROM [dbo].[GROUPS]
DELETE FROM [dbo].[FACULTY]

ALTER DATABASE University 
REMOVE FILE testFile
GO 

ALTER DATABASE University
REMOVE FILEGROUP fileGroup
GO  