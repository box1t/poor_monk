
# Classification (accuracy 0.92)

```python

import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, ConfusionMatrixDisplay
from sklearn.ensemble import RandomForestClassifier

# --- 1.1. Очистка от выбросов (IQR) ---
Q1 = df_clf['Insurance_Charges'].quantile(0.25)
Q3 = df_clf['Insurance_Charges'].quantile(0.75)
IQR = Q3 - Q1
df_ins_clean = df_clf[(df_clf['Insurance_Charges'] >= Q1 - 1.5*IQR) & 
                      (df_clf['Insurance_Charges'] <= Q3 + 1.5*IQR)].copy()

# --- 1.2. Создание таргета ---
median_val = df_ins_clean['Insurance_Charges'].median()
df_ins_clean['High_Charge'] = (df_ins_clean['Insurance_Charges'] > median_val).astype(int)

# --- 1.3. Признаки и Пайплайн ---
X = df_ins_clean.drop(columns=['Insurance_Charges', 'High_Charge'])
y = df_ins_clean['High_Charge']

cat_cols = X.select_dtypes(include=['object', 'str']).columns.tolist()
num_cols = X.select_dtypes(exclude=['object', 'str']).columns.tolist()

preprocessor_rf = ColumnTransformer([
    ('num', StandardScaler(), num_cols),
    ('cat', OneHotEncoder(handle_unknown='ignore'), cat_cols) 
    # handle_unknown='ignore' полезен для RF, чтобы не падать на новых категориях
])

model_rf = Pipeline([
    ('pre', preprocessor_rf),
    ('clf', RandomForestClassifier(
        n_estimators=100, 
        max_depth=10, 
        random_state=42, 
        class_weight='balanced'
    ))
])

# Обучение
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, stratify=y, random_state=42)
model_rf.fit(X_train, y_train)
# --- 2.3. Результаты ---
print("РЕЗУЛЬТАТЫ: СТРАХОВАНИЕ (КЛАССИФИКАЦИЯ)")
print(classification_report(y_test, model_rf.predict(X_test)))

```

# Regression (MAE: 5.88 MSE: 102.54 RMSE: 10.13 R2: 0.9025)


```python

from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, r2_score, mean_squared_error
from sklearn.ensemble import RandomForestRegressor

# --- 2.1. Очистка GFR от выбросов ---
Q1_k = df_reg['GFR'].quantile(0.25)
Q3_k = df_reg['GFR'].quantile(0.75)
IQR_k = Q3_k - Q1_k
df_kid_clean = df_reg[(df_reg['GFR'] >= Q1_k - 1.5*IQR_k) & 
                      (df_reg['GFR'] <= Q3_k + 1.5*IQR_k)].copy()

# --- 2.2. Признаки (УДАЛЯЕМ КРЕАТИНИН для честности) ---
X_k = df_kid_clean.drop(columns=['GFR', 'CKD_Status', 'Medication', 'Creatinine'])
y_k = df_kid_clean['GFR']

num_k = X_k.select_dtypes(exclude=['object', 'str']).columns.tolist()

# --- 2.3. Пайплайн ---
preprocessor_rf_k = ColumnTransformer([
    ('num', StandardScaler(), num_k)
])

model_rf_reg = Pipeline([
    ('pre', preprocessor_rf_k),
    ('reg', RandomForestRegressor(
        n_estimators=200,     # Количество деревьев
        max_depth=None,       # Глубина (можно ограничить для борьбы с переобучением)
        min_samples_leaf=3,   # Минимум объектов в листе (помогает сглаживать прогноз)
        random_state=42,
        n_jobs=-1             # Использовать все ядра процессора для ускорения
    ))
])

# Обучение
X_train_k, X_test_k, y_train_k, y_test_k = train_test_split(X_k, y_k, test_size=0.2, random_state=42)
model_rf_reg.fit(X_train_k, y_train_k)

# Оценка
y_pred_rf_k = model_rf_reg.predict(X_test_k)

print("\nРЕЗУЛЬТАТЫ: ПОЧКИ (РЕГРЕССИЯ БЕЗ КРЕАТИНИНА)")
print(f"MAE: {mean_absolute_error(y_test_k, y_pred_rf_k):.2f}")
print(f"MSE: {mean_squared_error(y_test_k, y_pred_rf_k):.2f}")

print(f"RMSE: {np.sqrt(mean_squared_error(y_test_k, y_pred_rf_k)):.2f}")
print(f"R2: {r2_score(y_test_k, y_pred_rf_k):.4f}")

```