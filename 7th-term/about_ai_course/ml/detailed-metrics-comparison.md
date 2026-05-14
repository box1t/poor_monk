
https://gemini.google.com/app/adc966cc1da7c9c7

### 📊 Детальные метрики по категориям
<details>
<summary><b>🔍 1. Метод ближайших соседей (KNN)</b></summary>

| Модель | Accuracy 🎯 | R² Score 📈 | MAE 📏 | RMSE 📉 | Статус |
| :--- | :---: | :---: | :---: | :---: | :---: |
| sklearn baseline | 0.88 | 0.8847 | 6.3669 | 11.0150 | ✅ |
| sklearn improved | 0.9172 (0.9045) | 0.9028 (0.8890) | 5.95 | 10.11 | 🚀 |
| **MyKNN** | 0.8981 | 0.9028 | 5.9525 | 10.1106 | 🛠️ |

</details>

<details>
<summary><b>📈 2. Линейные модели (Linear & Logistic)</b></summary>

| Модель | Accuracy 🎯 | R² Score 📈 | MAE 📏 | RMSE 📉 | Статус |
| :--- | :---: | :---: | :---: | :---: | :---: |
| sklearn baseline | 0.91 | 0.8715 | 7.72 | 11.63 | ✅ |
| sklearn improved | 0.93 | 0.8963 | 6.50 | 10.44 | 🚀 |
| **Mylinreg/Mylogreg** | 0.91 | 0.8715 | 7.73 | 11.6276 | 🛠️ |

</details>

<details>
<summary><b>🌳 3. Решающее дерево (Decision Tree)</b></summary>

| Модель | Accuracy 🎯 | R² Score 📈 | MAE 📏 | RMSE 📉 | Статус |
| :--- | :---: | :---: | :---: | :---: | :---: |
| sklearn baseline | 0.91 | 0.8917 | 6.31 | 10.67 | ✅ |
| sklearn improved | 0.91 | 0.8966 | 6.38 | 10.43 | 🚀 |
| **MyDecisionTree** | 0.0000 | 0.0000 | 0.0000 | 0.0000 | 🛠️ |

</details>

<details>
<summary><b>🌲 4. Случайный лес (Random Forest)</b></summary>

| Модель | Accuracy 🎯 | R² Score 📈 | MAE 📏 | RMSE 📉 | Статус |
| :--- | :---: | :---: | :---: | :---: | :---: |
| sklearn baseline | 0.92 | 0.9025 | 5.88 | 10.13 | ✅ |
| sklearn improved | 0.92 | 0.9045 (0.8948) | 5.91 | 10.02 | 🚀 |
| **MyRandomForest** | 0.0000 | 0.0000 | 0.0000 | 0.0000 | 🛠️ |

</details>

<details>
<summary><b>⚡ 5. Градиентный бустинг (Gradient Boosting)</b></summary>

| Модель | Accuracy 🎯 | R² Score 📈 | MAE 📏 | RMSE 📉 | Статус |
| :--- | :---: | :---: | :---: | :---: | :---: |
| xgboost baseline | 0.94 | 0.9003 | 6.01 | 10.24 | ✅ |
| xgboost improved | 0.91 | 0.9012 | 5.96 | 10.20 | 🚀 |
| **MyGB** | 0.0000 | 0.0000 | 0.0000 | 0.0000 | 🛠️ |

</details>