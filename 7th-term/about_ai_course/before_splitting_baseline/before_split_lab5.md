
# Classification (accuracy 0.94)

```python

import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OrdinalEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from xgboost import XGBClassifier # Импорт XGBoost
from sklearn.metrics import classification_report

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

cat_cols = X.select_dtypes(include=['object', 'category']).columns.tolist()
num_cols = X.select_dtypes(exclude=['object', 'category']).columns.tolist()

# Кодируем категории в числа для XGBoost
preprocessor = ColumnTransformer([
    ('num', 'passthrough', num_cols),
    ('cat', OrdinalEncoder(handle_unknown='use_encoded_value', unknown_value=-1), cat_cols)
])

# Настройка модели XGBoost
model_xgb = Pipeline([
    ('pre', preprocessor),
    ('clf', XGBClassifier(
        n_estimators=100,      # Количество деревьев
        learning_rate=0.1,     # Шаг обучения
        max_depth=4,           # Глубина дерева
        use_label_encoder=False, 
        eval_metric='logloss', # Метрика для оценки в процессе обучения
        random_state=42
    ))
])

# --- 1.4. Обучение и оценка ---
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, stratify=y, random_state=42)
model_xgb.fit(X_train, y_train)

print("РЕЗУЛЬТАТЫ: XGBOOST (КЛАССИФИКАЦИЯ)")
y_pred = model_xgb.predict(X_test)
print(classification_report(y_test, y_pred))

```

# Regression (MAE: 6.05, MSE: 109.31, RMSE: 10.46, R2: 0.8961)

```python

import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OrdinalEncoder # Для работы с категориями
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from xgboost import XGBRegressor # Модель для регрессии
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

# --- 2.1. Очистка GFR от выбросов ---
Q1_k = df_reg['GFR'].quantile(0.25)
Q3_k = df_reg['GFR'].quantile(0.75)
IQR_k = Q3_k - Q1_k
df_kid_clean = df_reg[(df_reg['GFR'] >= Q1_k - 1.5*IQR_k) & 
                      (df_reg['GFR'] <= Q3_k + 1.5*IQR_k)].copy()

# --- 2.2. Признаки (УДАЛЯЕМ КРЕАТИНИН) ---
X_k = df_kid_clean.drop(columns=['GFR', 'CKD_Status', 'Medication', 'Creatinine'])
y_k = df_kid_clean['GFR']

# Определяем колонки
cat_cols = X_k.select_dtypes(include=['object', 'str']).columns.tolist()
num_cols = X_k.select_dtypes(exclude=['object', 'str']).columns.tolist()

# --- 2.3. Пайплайн ---
# Для XGBoost масштабирование (StandardScaler) не обязательно, 
# но мы оставим простую обработку через ColumnTransformer.
preprocessor_k = ColumnTransformer([
    ('num', 'passthrough', num_cols),
    ('cat', OrdinalEncoder(handle_unknown='use_encoded_value', unknown_value=-1), cat_cols)
])

model_reg_xgb = Pipeline([
    ('pre', preprocessor_k),
    ('reg', XGBRegressor(
        n_estimators=200,      # Больше деревьев для точности
        learning_rate=0.05,    # Меньше шаг — выше точность (но дольше учится)
        max_depth=4,           # Глубина деревьев
        subsample=0.8,         # Использование 80% данных для борьбы с переобучением
        random_state=42
    ))
])

# --- 2.4. Обучение и оценка ---
X_train_k, X_test_k, y_train_k, y_test_k = train_test_split(X_k, y_k, test_size=0.2, random_state=42)
model_reg_xgb.fit(X_train_k, y_train_k)

# Прогноз
y_pred_k = model_reg_xgb.predict(X_test_k)

print("\nРЕЗУЛЬТАТЫ: XGBOOST РЕГРЕССИЯ (GFR)")
print(f"MAE: {mean_absolute_error(y_test_k, y_pred_k):.2f}")
print(f"MSE: {mean_squared_error(y_test_k, y_pred_k):.2f}")
print(f"RMSE: {np.sqrt(mean_squared_error(y_test_k, y_pred_k)):.2f}")
print(f"R2: {r2_score(y_test_k, y_pred_k):.4f}")

```