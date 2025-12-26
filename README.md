#  Detector de anomalías financieras v1.0

Este proyecto nace de la intersección entre la **Auditoría Forense** y el **Desarrollo de Software de Alto Rendimiento**.

#  Desafío Técnico
En entornos de Big Data Financiero, las herramientas tradicionales (como Excel) pueden volverse lentas. Este detector, desarrollado en **C++**, procesa datos a una velocidad significativamente mayor, permitiendo auditorías en tiempo real.

#  Lógica de Detección
El sistema utiliza el método de **Puntuación Z (Z-Score)** para identificar transacciones sospechosas:
- Se calcula la media y la desviación estándar del conjunto de datos.
- Cualquier transacción que se desvíe más de **3 unidades estándar** es marcada automáticamente para revisión humana.

#  Rendimiento
- **Capacidad:** Procesamiento de 1,000+ registros.
- **Latencia:** < 5ms (dependiendo del hardware).
