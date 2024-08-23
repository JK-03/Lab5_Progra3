#include "cframe.h"
#include "ui_cframe.h"
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
    this->setWindowTitle("Laboratorio #5");
}

cframe::~cframe()
{
    delete ui;
}

void cframe::on_pushButton_clicked()
{
    std::string opcion = "";

    QMessageBox msgBox;
    msgBox.setText("Por favor, seleccione una opción:");

    QPushButton *opcion6 = msgBox.addButton("Salir", QMessageBox::ActionRole);
    QPushButton *opcion5 = msgBox.addButton("Ejercicio #4", QMessageBox::ActionRole);
    QPushButton *opcion4 = msgBox.addButton("Ejercicio #3", QMessageBox::ActionRole);
    QPushButton *opcion3 = msgBox.addButton("Ejercicio #2", QMessageBox::ActionRole);
    QPushButton *opcion2 = msgBox.addButton("Ejercicio #1", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == opcion2) {
        ui->tabWidget->setCurrentIndex(1);
    } else if (msgBox.clickedButton() == opcion3) {
        ui->tabWidget->setCurrentIndex(2);
    } else if (msgBox.clickedButton() == opcion4) {
        ui->tabWidget->setCurrentIndex(3);
    } else if (msgBox.clickedButton() == opcion5) {
        ui->tabWidget->setCurrentIndex(4);
    } else if (msgBox.clickedButton() == opcion6) {
        this->close();
    }
}

//EJERCICIO #1
void cframe::on_pushButton_2_clicked()
{
    int filaPrimera = ui->SPB_FilaPrimera->value();
    int columnaPrimera = ui->SPB_ColumnaPrimera->value();

    int filaSegunda = ui->SPB_FilaSegunda->value();
    int columnaSegunda = ui->SPB_ColumnaSegunda->value();

    if (filaPrimera <= 0 || columnaPrimera <= 0 || filaSegunda <= 0 || columnaSegunda <= 0) {
        QMessageBox::warning(this, "Error", "Las dimensiones de las matrices deben ser mayores que cero.");
        return;
    }

    srand(static_cast<unsigned>(time(nullptr)));

    int **matriz1 = new int*[filaPrimera];
    int **matriz2 = new int*[filaSegunda];
    int **resultado;

    for (int i = 0; i < filaPrimera; ++i) {
        matriz1[i] = new int[columnaPrimera];
    }
    for (int i = 0; i < filaSegunda; ++i) {
        matriz2[i] = new int[columnaSegunda];
    }

    ui->tableWidget_2->setRowCount(filaPrimera);
    ui->tableWidget_2->setColumnCount(columnaPrimera);
    for (int i = 0; i < filaPrimera; ++i) {
        for (int j = 0; j < columnaPrimera; ++j) {
            matriz1[i][j] = rand() % 100;
            ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(QString::number(matriz1[i][j])));
        }
    }

    ui->tableWidget_3->setRowCount(filaSegunda);
    ui->tableWidget_3->setColumnCount(columnaSegunda);
    for (int i = 0; i < filaSegunda; ++i) {
        for (int j = 0; j < columnaSegunda; ++j) {
            matriz2[i][j] = rand() % 100;
            ui->tableWidget_3->setItem(i, j, new QTableWidgetItem(QString::number(matriz2[i][j])));
        }
    }

    QMessageBox msgBox;
    msgBox.setText("Por favor, seleccione una opción:");

    QPushButton *opcionMultiplicar = msgBox.addButton("Multiplicar las dos matrices", QMessageBox::ActionRole);
    QPushButton *opcionRestar = msgBox.addButton("Restar la segunda matriz de la primera", QMessageBox::ActionRole);
    QPushButton *opcionSumar = msgBox.addButton("Sumar las dos matrices", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == opcionSumar) {
        if (filaPrimera != filaSegunda || columnaPrimera != columnaSegunda) {
            QMessageBox::warning(this, "Error", "Las dimensiones de las matrices no coinciden para la suma.");
        } else {
            resultado = new int*[filaPrimera];
            for (int i = 0; i < filaPrimera; ++i) {
                resultado[i] = new int[columnaPrimera];
            }

            for (int i = 0; i < filaPrimera; ++i) {
                for (int j = 0; j < columnaPrimera; ++j) {
                    resultado[i][j] = matriz1[i][j] + matriz2[i][j];
                }
            }

            ui->tableWidget_4->setRowCount(filaPrimera);
            ui->tableWidget_4->setColumnCount(columnaPrimera);
            for (int i = 0; i < filaPrimera; ++i) {
                for (int j = 0; j < columnaPrimera; ++j) {
                    ui->tableWidget_4->setItem(i, j, new QTableWidgetItem(QString::number(resultado[i][j])));
                }
            }

            for (int i = 0; i < filaPrimera; ++i) {
                delete[] resultado[i];
            }
            delete[] resultado;
        }

    } else if (msgBox.clickedButton() == opcionRestar) {
        if (filaPrimera != filaSegunda || columnaPrimera != columnaSegunda) {
            QMessageBox::warning(this, "Error", "Las dimensiones de las matrices no coinciden para la resta.");
        } else {
            resultado = new int*[filaPrimera];
            for (int i = 0; i < filaPrimera; ++i) {
                resultado[i] = new int[columnaPrimera];
            }

            for (int i = 0; i < filaPrimera; ++i) {
                for (int j = 0; j < columnaPrimera; ++j) {
                    resultado[i][j] = matriz1[i][j] - matriz2[i][j];
                }
            }

            ui->tableWidget_4->setRowCount(filaPrimera);
            ui->tableWidget_4->setColumnCount(columnaPrimera);
            for (int i = 0; i < filaPrimera; ++i) {
                for (int j = 0; j < columnaPrimera; ++j) {
                    ui->tableWidget_4->setItem(i, j, new QTableWidgetItem(QString::number(resultado[i][j])));
                }
            }

            for (int i = 0; i < filaPrimera; ++i) {
                delete[] resultado[i];
            }
            delete[] resultado;
        }

    } else if (msgBox.clickedButton() == opcionMultiplicar) {
        if (columnaPrimera != filaSegunda) {
            QMessageBox::warning(this, "Error", "Las matrices no se pueden multiplicar debido a sus dimensiones.");
        } else {
            resultado = new int*[filaPrimera];
            for (int i = 0; i < filaPrimera; ++i) {
                resultado[i] = new int[columnaSegunda];
            }

            for (int i = 0; i < filaPrimera; ++i) {
                for (int j = 0; j < columnaSegunda; ++j) {
                    resultado[i][j] = 0;
                }
            }

            for (int i = 0; i < filaPrimera; ++i) {
                for (int j = 0; j < columnaSegunda; ++j) {
                    for (int k = 0; k < columnaPrimera; ++k) {
                        resultado[i][j] += matriz1[i][k] * matriz2[k][j];
                    }
                }
            }

            ui->tableWidget_4->setRowCount(filaPrimera);
            ui->tableWidget_4->setColumnCount(columnaSegunda);
            for (int i = 0; i < filaPrimera; ++i) {
                for (int j = 0; j < columnaSegunda; ++j) {
                    ui->tableWidget_4->setItem(i, j, new QTableWidgetItem(QString::number(resultado[i][j])));
                }
            }

            for (int i = 0; i < filaPrimera; ++i) {
                delete[] resultado[i];
            }
            delete[] resultado;
        }
    }

    for (int i = 0; i < filaPrimera; ++i) {
        delete[] matriz1[i];
    }
    delete[] matriz1;

    for (int i = 0; i < filaSegunda; ++i) {
        delete[] matriz2[i];
    }
    delete[] matriz2;
}

//EJERCICIO #2
void cframe::on_pushButton_5_clicked()
{
    ui->tabWidget->setCurrentIndex(5);
}

void cframe::on_pushButton_3_clicked()
{
    int filas = ui->SPB_FilaBuscar->value();
    int columnas = ui->SPB_ColumnaBuscar->value();

    if (filas <= 0 || columnas <= 0) {
        QMessageBox::warning(this, "Error", "Las filas y columnas deben ser mayores que cero.");
        return;
    }

    srand(static_cast<unsigned>(time(nullptr)));

    int **matriz = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new int[columnas];
    }

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = rand() % 100;
        }
    }

    ui->tableWidget_5->setRowCount(filas);
    ui->tableWidget_5->setColumnCount(columnas);

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            ui->tableWidget_5->setItem(i, j, new QTableWidgetItem(QString::number(matriz[i][j])));
        }
    }

    for (int i = 0; i < filas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void cframe::on_pushButton_4_clicked()
{
    int numeroBuscado = ui->SPB_NumeroBuscar->value();
    int filas = ui->tableWidget_5->rowCount();
    int columnas = ui->tableWidget_5->columnCount();

    bool matrizGenerada = false;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (ui->tableWidget_5->item(i, j) != nullptr) {
                matrizGenerada = true;
                break;
            }
        }
        if (matrizGenerada) break;
    }

    if (!matrizGenerada) {
        QMessageBox::warning(this, "Error", "No hay ninguna matriz generada en el tableWidget.");
        return;
    }

    bool encontrado = false;
    int filaEncontrada = -1;
    int columnaEncontrada = -1;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            QTableWidgetItem *item = ui->tableWidget_5->item(i, j);
            if (item) {
                int valor = item->text().toInt();
                if (valor == numeroBuscado) {
                    encontrado = true;
                    filaEncontrada = i;
                    columnaEncontrada = j;
                    break;
                }
            }
        }
        if (encontrado) break;
    }

    if (encontrado) {
        QString mensaje = QString("Número encontrado en la fila %1, columna %2")
                              .arg(filaEncontrada + 1).arg(columnaEncontrada + 1);
        QMessageBox::information(this, "Resultado de Búsqueda", mensaje);
    } else {
        QMessageBox::information(this, "Resultado de Búsqueda", "Número no encontrado en la matriz.");
    }
}

//EJERCICIO #3
void cframe::on_pushButton_6_clicked()
{
    int filas = ui->SPB_FilaTrans->value();
    int columnas = ui->SPB_ColumnaTrans->value();

    if (filas <= 0 || columnas <= 0) {
        QMessageBox::warning(this, "Error", "Las filas y columnas deben ser mayores que cero.");
        return;
    }

    int **matrizOriginal = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        matrizOriginal[i] = new int[columnas];
    }

    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matrizOriginal[i][j] = rand() % 100;
        }
    }

    int **matrizTranspuesta = new int*[columnas];
    for (int i = 0; i < columnas; ++i) {
        matrizTranspuesta[i] = new int[filas];
    }

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matrizTranspuesta[j][i] = matrizOriginal[i][j];
        }
    }

    //TRANSPUESTA
    ui->tableWidget_6->setRowCount(filas);
    ui->tableWidget_6->setColumnCount(columnas);
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            ui->tableWidget_6->setItem(i, j, new QTableWidgetItem(QString::number(matrizOriginal[i][j])));
        }
    }

    ui->tableWidget_7->setRowCount(columnas);
    ui->tableWidget_7->setColumnCount(filas);
    for (int i = 0; i < columnas; ++i) {
        for (int j = 0; j < filas; ++j) {
            ui->tableWidget_7->setItem(i, j, new QTableWidgetItem(QString::number(matrizTranspuesta[i][j])));
        }
    }

    for (int i = 0; i < filas; ++i) {
        delete[] matrizOriginal[i];
    }
    delete[] matrizOriginal;

    for (int i = 0; i < columnas; ++i) {
        delete[] matrizTranspuesta[i];
    }
    delete[] matrizTranspuesta;
}

//EJERCICIO #4
void cframe::on_pushButton_7_clicked()
{
    int n = ui->SPB_Size->value();

    if (n <= 0) {
        QMessageBox::warning(this, "Error", "El tamaño de la matriz debe ser mayor que cero.");
        return;
    }

    int **matrizOriginal = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrizOriginal[i] = new int[n];
    }

    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizOriginal[i][j] = rand() % 100;
        }
    }

    int **matrizRotada = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrizRotada[i] = new int[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizRotada[j][n - 1 - i] = matrizOriginal[i][j];
        }
    }

    ui->tableWidget_8->setRowCount(n);
    ui->tableWidget_8->setColumnCount(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ui->tableWidget_8->setItem(i, j, new QTableWidgetItem(QString::number(matrizOriginal[i][j])));
        }
    }

    ui->tableWidget_9->setRowCount(n);
    ui->tableWidget_9->setColumnCount(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ui->tableWidget_9->setItem(i, j, new QTableWidgetItem(QString::number(matrizRotada[i][j])));
        }
    }

    for (int i = 0; i < n; ++i) {
        delete[] matrizOriginal[i];
        delete[] matrizRotada[i];
    }
    delete[] matrizOriginal;
    delete[] matrizRotada;
}
