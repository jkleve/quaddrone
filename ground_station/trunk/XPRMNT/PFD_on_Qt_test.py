import sys
from PyQt4 import QtGui,QtCore


app = QtGui.QApplication(sys.argv)

graphicsView = QtGui.QGraphicsView()
graphicsView.setGeometry(QtCore.QRect(600,300,250,250))
graphicsView.scene = QtGui.QGraphicsScene()

graphicsView.setScene(graphicsView.scene)

graphicsView.item = QtGui.QGraphicsEllipseItem(25,25,25,25)
graphicsView.scene.addItem(graphicsView.item)

graphicsView.show()
sys.exit(app.exec_())
