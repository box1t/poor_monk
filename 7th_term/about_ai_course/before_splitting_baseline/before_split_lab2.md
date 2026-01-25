
# Classification (accuracy 0.91)

```python

import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, ConfusionMatrixDisplay

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

preprocessor = ColumnTransformer([
    ('num', StandardScaler(), num_cols),
    ('cat', OneHotEncoder(drop='first'), cat_cols)
])

model_clf = Pipeline([
    ('pre', preprocessor),
    ('clf', LogisticRegression(class_weight='balanced', random_state=42))
])

# Обучение
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, stratify=y, random_state=42)
model_clf.fit(X_train, y_train)

print("РЕЗУЛЬТАТЫ: СТРАХОВАНИЕ (КЛАССИФИКАЦИЯ)")
print(classification_report(y_test, model_clf.predict(X_test)))

```



# Regression MAE: 7.72, MSE: 135.22, RMSE: 11.63, R2: 0.8715

```python

from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, r2_score, mean_squared_error

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
preprocessor_k = ColumnTransformer([
    ('num', StandardScaler(), num_k)
])

model_reg = Pipeline([
    ('pre', preprocessor_k),
    ('reg', LinearRegression())
])

# Обучение
X_train_k, X_test_k, y_train_k, y_test_k = train_test_split(X_k, y_k, test_size=0.2, random_state=42)
model_reg.fit(X_train_k, y_train_k)

# Оценка
y_pred_k = model_reg.predict(X_test_k)
print("\nРЕЗУЛЬТАТЫ: ПОЧКИ (РЕГРЕССИЯ БЕЗ КРЕАТИНИНА)")
print(f"MAE: {mean_absolute_error(y_test_k, y_pred_k):.2f}")
print(f"MSE: {mean_squared_error(y_test_k, y_pred_k):.2f}")

print(f"RMSE: {np.sqrt(mean_squared_error(y_test_k, y_pred_k)):.2f}")
print(f"R2: {r2_score(y_test_k, y_pred_k):.4f}")

```
