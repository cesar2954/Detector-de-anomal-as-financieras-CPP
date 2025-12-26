#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono> // Librería para medir tiempo movida al inicio

// 1. Estructura de datos
struct Transaction {
    int id;
    std::string date;
    double amount;
    bool isSuspicious;
};

// 2. Clase para el análisis
class AnomalyDetector {
public:
    // Función para cargar los datos del archivo CSV
    std::vector<Transaction> leerCSV(std::string nombreArchivo) {
        std::vector<Transaction> lista;
        std::ifstream archivo(nombreArchivo);
        std::string linea;

        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo abrir " << nombreArchivo << std::endl;
            return lista;
        }

        std::getline(archivo, linea); // Saltar encabezado

        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            Transaction t;
            std::string temp;

            std::getline(ss, temp, ','); t.id = std::stoi(temp);
            std::getline(ss, t.date, ',');
            std::getline(ss, temp, ','); t.amount = std::stod(temp);
            
            t.isSuspicious = false;
            lista.push_back(t);
        }
        archivo.close();
        return lista;
    }

    double calculateMean(const std::vector<Transaction>& transactions) {
        if (transactions.empty()) return 0;
        double sum = 0;
        for (const auto& t : transactions) sum += t.amount;
        return sum / transactions.size();
    }

    double calculateStdDev(const std::vector<Transaction>& transactions, double mean) {
        if (transactions.empty()) return 0;
        double sumSqDiff = 0;
        for (const auto& t : transactions) {
            sumSqDiff += pow(t.amount - mean, 2);
        }
        return sqrt(sumSqDiff / transactions.size());
    }

    void detect(std::vector<Transaction>& transactions) {
        double mean = calculateMean(transactions);
        double stdDev = calculateStdDev(transactions, mean);
        double threshold = 3.0; 

        std::cout << "\n--- Reporte de Analisis Estadistico ---" << std::endl;
        std::cout << "Promedio: $" << std::fixed << std::setprecision(2) << mean << std::endl;
        std::cout << "Desviacion Estandar: " << stdDev << std::endl;
        std::cout << "---------------------------------------" << std::endl;

        for (auto& t : transactions) {
            double zScore = std::abs(t.amount - mean) / stdDev;
            if (zScore > threshold) {
                t.isSuspicious = true;
            }
        }
    }
};

// 3. Función Principal (Solo una debe existir)
int main() {
    AnomalyDetector engine;

    // Medición de tiempo de inicio
    auto inicio = std::chrono::high_resolution_clock::now();

    // Cargar y Procesar
    std::vector<Transaction> myTransactions = engine.leerCSV("datos.csv");

    if (myTransactions.empty()) {
        std::cout << "Asegurate de ejecutar primero el generador.cpp para crear datos.csv" << std::endl;
        return 1;
    }

    engine.detect(myTransactions);

    // Medición de tiempo de fin
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tiempo = fin - inicio;

    // Mostrar resultados (Limitado a los primeros 20 para no saturar la terminal)
    std::cout << std::left << std::setw(5) << "ID" << std::setw(15) << "MONTO" << "ESTADO" << std::endl;
    int count = 0;
    for (const auto& t : myTransactions) {
        if (t.isSuspicious || count < 15) { // Muestra anomalías y algunas normales
            std::cout << std::left << std::setw(5) << t.id 
                      << "$" << std::setw(14) << t.amount 
                      << (t.isSuspicious ? "[!!!] SOSPECHOSA" : "Normal") 
                      << std::endl;
        }
        count++;
    }

    std::cout << "\n>>> Procesamiento completado." << std::endl;
    std::cout << ">>> Tiempo total: " << tiempo.count() << " ms" << std::endl;
    

    return 0;
}