import operator


import sys
K=sys.argv
import socket
U=socket.error
P=socket.SOCK_STREAM
C=socket.AF_INET
h=socket.socket
import json
zX=json.loads
zR=json.dumps
"""
from PyQt5.QtCore import QSize,pyqtSlot
from PyQt5.QtWidgets import QMainWindow,QTabWidget,QWidget,QFormLayout,QLineEdit,QPushButton,QVBoxLayout,QMessageBox,QTableWidget,QAbstractItemView,QAbstractScrollArea,QComboBox,QHeaderView,QTableWidgetItem,QApplication
import logging
zB=logging.getLogger
zF=logging.ERROR
zw=logging.basicConfig
z="%(levelname)s %(asctime)s - %(message)s"
zw(filename="logfile.log",filemode="w",format=z,level=zF)
X=zB()
X.error("Our First Log Message")
w=h(C,P)
F=('127.0.0.1',8888)
B=list()
class N(QMainWindow):
 def __init__(v):
  super().__init__()
  v.setMinimumSize(QSize(70,70))
  v.setWindowTitle("Авторизация")
  j=QVBoxLayout()
  v.setLayout(j)
  p=QTabWidget()
  p.addTab(v.a(),"Войти")
  p.addTab(v.u(),"Регистрация")
  j.addWidget(p)
  w=QWidget()
  w.setLayout(j)
  v.setCentralWidget(w)
  w.show()
 def a(v)->QWidget:
  D=QWidget()
  j=QFormLayout()
  v.e_name_in=QLineEdit()
  v.e_pass_in=QLineEdit()
  A=QPushButton('Войти',v)
  A.clicked.connect(v.O)
  j.addRow('Логин',v.e_name_in)
  j.addRow('Пароль',v.e_pass_in)
  j.addRow(A)
  D.setLayout(j)
  return D
 def a(v):
  def G():
   B[1]=QFormLayout()
   return QVBoxLayout()
  B=[QWidget(),QFormLayout(),QWidget(),QFormLayout()]
  v.e_name_in=QLineEdit()
  v.e_pass_in=QLineEdit()
  v.e_name_reg=QLineEdit()
  v.e_pass_reg=QLineEdit()
  A=QPushButton('Войти',v)
  A.clicked.connect(v.O)
  B[1].addRow('Логин',v.e_name_in)
  B[1].addRow('Пароль',v.e_pass_in)
  B[1].addRow(A)
  B[0].setLayout(B[1])
  if B[0]is not B[2]:
   B[2]=G()
  return B[0]
 def u(v)->QWidget:
  V=QWidget()
  j=QFormLayout()
  v.e_name_up=QLineEdit()
  v.e_pass_up=QLineEdit()
  v.e_pass_up_check=QLineEdit()
  m=QPushButton('Регистрация',v)
  m.clicked.connect(v.T)
  j.addRow('Логин',v.e_name_up)
  j.addRow('Пароль',v.e_pass_up)
  j.addRow('Повт. пароль',v.e_pass_up_check)
  j.addRow(m)
  V.setLayout(j)
  return V
 def d(v,title:str,msg:str):
  W=QMessageBox()
  W.setIcon(QMessageBox.Critical)
  W.setText(msg)
  W.setWindowTitle(title)
  W.exec_()
 @pyqtSlot()
 def O(v):
  S=zR(['in',v.e_name_in.text(),v.e_pass_in.text()]).encode()
  print('Send',S)
  try:
   S=zX(o(S))
   print('Get',S)
   if S[0]=="wrong input":
    v.d('Ошибка','Неправильный логин или пароль')
   else:
    global B
    B=S
    v.close()
    v.window=f()
    v.window.show()
  except:
   X.exception('фронт ошибка')
   v.d('Ошибка','Непредвиденный ответ с сервера!')
 @pyqtSlot()
 def T(v):
  S=zR(['up',v.e_name_up.text(),v.e_pass_up.text()]).encode()
  print('Send',S)
  try:
   S=zX(o(S))
   print('Get',S)
   if S[0]=="already exist":
    v.d('Ошибка','Данный пользователь уже зарегистрирован')
   else:
    global B
    B=S
    v.close()
    v.window=f()
    v.window.show()
  except:
   X.exception('фронт ошибка')
   v.d('Ошибка','Непредвиденный ответ с сервера!')
class f(QMainWindow):
 def __init__(v):
  super().__init__()
  print(B)
  v.setMinimumSize(QSize(70,70))
  v.setWindowTitle("Из рук в руки")
  j=QVBoxLayout()
  v.setLayout(j)
  p=QTabWidget()
  p.addTab(v.H(),"Просмотр книг")
  p.addTab(v.M(),"Разместить объявление")
  if B[0][2]==2:
   p.addTab(v.g(),"Управление ролями")
  j.addWidget(p)
  w=QWidget()
  w.setLayout(j)
  v.setCentralWidget(w)
 def H(v)->QWidget:
  J=QWidget()
  j=QFormLayout()
  v.t_book=QTableWidget()
  v.t_book.setColumnCount(6)
  v.t_book.setHorizontalHeaderLabels(["Название","Жанр","Автор","Цена","Телефон","Разместил"])
  v.k()
  v.t_book.setEditTriggers(QAbstractItemView.NoEditTriggers)
  v.t_book.setSelectionBehavior(QAbstractItemView.SelectRows)
  v.t_book.itemDoubleClicked.connect(v.i)
  v.t_book.setSizeAdjustPolicy(QAbstractScrollArea.AdjustToContentsOnFirstShow)
  I=v.t_book.horizontalHeader()
  I.setSectionResizeMode(0,QHeaderView.Stretch)
  for i in range(1,6):
   I.setSectionResizeMode(i,QHeaderView.ResizeToContents)
  v.t_book.horizontalHeader().setStretchLastSection(True)
  j.addWidget(v.t_book)
  E=QPushButton('Обновить',v)
  E.clicked.connect(v.x)
  j.addRow(E)
  J.setLayout(j)
  return J
 def M(v)->QWidget:
  q=QWidget()
  j=QFormLayout()
  v.e_name=QLineEdit()
  v.e_name.setPlaceholderText("Последнее желание")
  j.addRow('Название произведения',v.e_name)
  v.c_catg=QComboBox()
  v.c_catg.addItem("Фэнтези")
  v.c_catg.addItem("Детективы")
  v.c_catg.addItem("Ужасы")
  v.c_catg.addItem("Поэзия")
  v.c_catg.addItem("Фантастика")
  v.c_catg.addItem("Любовные романы")
  v.c_catg.addItem("Триллеры")
  v.c_catg.addItem("Комиксы и манга")
  v.c_catg.addItem("Проза")
  j.addRow("Жанр произведения",v.c_catg)
  v.e_auth=QLineEdit()
  v.e_auth.setPlaceholderText("Анджей Сапковский")
  j.addRow('Автор произведения',v.e_auth)
  v.e_pric=QLineEdit()
  v.e_pric.setPlaceholderText("20 руб.")
  j.addRow('Цена за товар',v.e_pric)
  v.e_phone=QLineEdit()
  v.e_phone.setPlaceholderText("+375(29) 333-33-33")
  j.addRow('Телефон для связи',v.e_phone)
  Y=QPushButton('Разместить',v)
  Y.clicked.connect(v.n)
  j.addRow(Y)
  q.setLayout(j)
  return q
 def g(v)->QWidget:
  s=QWidget()
  j=QFormLayout()
  v.t_user=QTableWidget()
  v.t_user.setColumnCount(2)
  v.t_user.setHorizontalHeaderLabels(["Пользователь","Роль"])
  v.Q()
  v.t_user.setEditTriggers(QAbstractItemView.NoEditTriggers)
  v.t_user.setSelectionBehavior(QAbstractItemView.SelectRows)
  v.t_user.itemDoubleClicked.connect(v.c)
  v.t_user.setSizeAdjustPolicy(QAbstractScrollArea.AdjustToContentsOnFirstShow)
  I=v.t_user.horizontalHeader()
  I.setSectionResizeMode(0,QHeaderView.Stretch)
  for i in range(1,2):
   I.setSectionResizeMode(i,QHeaderView.ResizeToContents)
  v.t_user.horizontalHeader().setStretchLastSection(True)
  j.addWidget(v.t_user)
  E=QPushButton('Обновить',v)
  E.clicked.connect(v.y)
  j.addRow(E)
  s.setLayout(j)
  return s
 def d(v,title:str,msg:str):
  W=QMessageBox()
  W.setIcon(QMessageBox.Critical)
  W.setText(msg)
  W.setWindowTitle(title)
  W.exec_()
 @pyqtSlot()
 def k(v):
  b=B[1]
  v.t_book.setRowCount(len(b))
  for i in range(len(b)):
   v.t_book.setItem(i,0,QTableWidgetItem(b[i][1]))
   v.t_book.setItem(i,1,QTableWidgetItem(b[i][2]))
   v.t_book.setItem(i,2,QTableWidgetItem(b[i][3]))
   v.t_book.setItem(i,3,QTableWidgetItem(b[i][4]))
   v.t_book.setItem(i,4,QTableWidgetItem(b[i][5]))
   v.t_book.setItem(i,5,QTableWidgetItem(b[i][6]))
 @pyqtSlot()
 def x(v):
  try:
   S=zR(['books',B[0][0],B[0][1]]).encode()
   print('Send',S)
   S=zX(o(S))
   print('Get',S)
   B[1]=S
   v.k()
  except:
   X.exception('фронт ошибка')
   v.d('Ошибка','Ошибка при обновлении книг со стороны сервера')
 @pyqtSlot()
 def Q(v):
  l=B[2]
  v.t_user.setRowCount(len(l))
  for i in range(len(l)):
   t='Модератор' if l[i][2]==2 else 'Пользователь'
   v.t_user.setItem(i,0,QTableWidgetItem(l[i][1]))
   v.t_user.setItem(i,1,QTableWidgetItem(t))
 @pyqtSlot()
 def y(v):
  try:
   S=zR(['users',B[0][0],B[0][1]]).encode()
   print('Send',S)
   S=zX(o(S))
   print('Get',S)
   if S[0]=='permission denied':
    v.d('Ошибка','Доступ запрещён')
   else:
    B[2]=S
    v.Q()
  except:
   X.exception('фронт ошибка')
   v.d('Ошибка','Ошибка при обновлении пользователей со стороны сервера')
 @pyqtSlot()
 def i(v):
  if v.t_book.item(v.t_book.currentRow(),5).text()==B[0][0]or B[0][2]==2:
   try:
    S=zR(['delete book',B[0][0],B[0][1],B[1][v.t_book.currentRow()][0]]).encode()
    print('Send',S)
    S=zX(o(S))
    print('Get',S)
    if S[0]=='no delete book':
     v.d('Ошибка','Удалить не получилось!')
    v.x()
   except:
    X.exception('фронт ошибка')
    v.d('Ошибка','Ошибка при удалении со стороны сервера')
 @pyqtSlot()
 def n(v):
  try:
   S=zR(['create book',B[0][0],B[0][1],v.e_name.text(),v.c_catg.currentText(),v.e_auth.text(),v.e_pric.text(),v.e_phone.text()]).encode()
   print('Send',S)
   S=zX(o(S))
   print('Get',S)
   if S[0]=='no create book':
    v.d('Ошибка','Разместить объявление не получилось!')
   v.x()
  except:
   X.exception('фронт ошибка')
   v.d('Ошибка','Ошибка при размещении со стороны сервера')
 @pyqtSlot()
 def c(v):
  if B[0][2]==2:
   try:
    S=zR(['update role',B[0][0],B[0][1],B[2][v.t_user.currentRow()][0]]).encode()
    print('Send',S)
    S=zX(o(S))
    print('Get',S)
    if S[0]=='no update role':
     v.d('Ошибка','Изменить роль не вышло!')
    v.y()
   except:
    X.exception('фронт ошибка')
    v.d('Ошибка','Ошибка при обновлении роли со стороны сервера')
def L():
 try:
  w.connect(F)
 except U:
  X.exception('Server not responding')
  print('Server not responding')
def o(S:str)->str:
 try:
  w.send(S)
  return w.recv(2048).decode()
 except U:
  return 'bad request'
if __name__=="__main__":
 e=QApplication(K)
 r=N()
 r.show()
 L()
 e.exec_()
def DUG():
 Da.bind(DS)
 Da.listen()
 global DB
 while not DB:
  try:
   Dr,Dy=Da.accept()
   if Dy in DV:
    print('Ban connection',Dy)
    Dr.close()
   else:
    print('Get connection',Dy)
    t=DX(target=DM,args=(Dr,Dy))
    t.start()
  except:
   DV.append(Dy)
   print('Connection lost',Dy)
   logger.exception('Connection lost')
   Dr.close()
def DM(De,client_addr):
 try:
  while True:
   Dd=De.recv(2048).decode()
   print(DK(Dd))
   if DK(Dd)>2048:
    print('Catch buffer overflow from',client_addr)
    De.close()
    return
   if not Dd:
    break
   print('GET FROM',client_addr,Dd,DK(Dd),'bytes')
   Dd=DU(Dd,client_addr)
   print('SEND TO',client_addr,Dd)
   De.sendall(Dd.encode())
 except Exception as exc:
  print(f'Connection lost (reason: {exc})',client_addr)
  logger.exception('Connection lost')
  DV.append(client_addr)
 finally:
  De.close()"""

def interpret (data):
    # array = [78, 41, 4, 27, 3, 27, 8, 39, 19, 34, 6, 41, 13, 52, 16]
    print(merge_sort(data))

def interpret2 (n):
    # array = [78, 41, 4, 27, 3, 27, 8, 39, 19, 34, 6, 41, 13, 52, 16]
    # n = int(input())
    factorial = 1
    while n > 1:
        factorial *= n
        n -= 1

    print(factorial)

def merge(left, right, compare):
    result = []
    i, j = 0, 0
    while i < len(left) and j < len(right):
        if compare(left[i], right[j]):
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    while i < len(left):
        result.append(left[i])
        i += 1
    while j < len(right):
        result.append(right[j])
        j += 1
    return result

def merge_sort(L, compare=operator.lt):
    if len(L) < 2:
        return L[:]
    else:
        middle = int(len(L) / 2)
        left = merge_sort(L[:middle], compare)
        right = merge_sort(L[middle:], compare)
        return merge(left, right, compare)

# array = [78, 41, 4, 27, 3, 27, 8, 39, 19, 34, 6, 41, 13, 52, 16]


