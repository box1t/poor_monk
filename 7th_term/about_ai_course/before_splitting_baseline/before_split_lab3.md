
# Classification (accuracy 0.91)

```python

import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.tree import DecisionTreeClassifier, plot_tree # Добавили дерево и визуализацию
from sklearn.metrics import classification_report, ConfusionMatrixDisplay
import matplotlib.pyplot as plt

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
    ('cat', OneHotEncoder(handle_unknown='ignore'), cat_cols) # Убрали drop='first', для деревьев это не критично
])

# Заменяем LogisticRegression на DecisionTreeClassifier
model_tree = Pipeline([
    ('pre', preprocessor),
    ('clf', DecisionTreeClassifier(
        max_depth=5,              # Ограничим глубину, чтобы дерево не переобучилось
        min_samples_leaf=10,      # Минимальное кол-во объектов в листе
        class_weight='balanced', 
        random_state=42
    ))
])

# Обучение
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, stratify=y, random_state=42)
model_tree.fit(X_train, y_train)

# --- РЕЗУЛЬТАТЫ ---
print("РЕЗУЛЬТАТЫ: DECISION TREE (КЛАССИФИКАЦИЯ)")
y_pred = model_tree.predict(X_test)
print(classification_report(y_test, y_pred))

plt.figure(figsize=(20,10))
plot_tree(model_tree.named_steps['clf'], 
          feature_names=model_tree.named_steps['pre'].get_feature_names_out(),
          class_names=['Low', 'High'],
          filled=True, fontsize=10)
plt.show()
```

# Regression (MAE: 6.31 RMSE: 10.67 R2: 0.8917)

```python

import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.tree import DecisionTreeRegressor  # Специальная модель для регрессии
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

model_tree_reg = Pipeline([
    ('pre', preprocessor_k),
    ('reg', DecisionTreeRegressor(
        max_depth=6,              # Ограничение глубины крайне важно для регрессии
        min_samples_leaf=5,       # Минимум объектов в листе, чтобы избежать шума
        random_state=42
    ))
])

# Обучение
X_train_k, X_test_k, y_train_k, y_test_k = train_test_split(X_k, y_k, test_size=0.2, random_state=42)
model_tree_reg.fit(X_train_k, y_train_k)

# Оценка
y_pred_k = model_tree_reg.predict(X_test_k)

print("\nРЕЗУЛЬТАТЫ: DECISION TREE REGRESSOR (GFR)")
print(f"MAE: {mean_absolute_error(y_test_k, y_pred_k):.2f}")
print(f"MSE: {mean_squared_error(y_test_k, y_pred_k):.2f}")
print(f"RMSE: {np.sqrt(mean_squared_error(y_test_k, y_pred_k)):.2f}")
print(f"R2: {r2_score(y_test_k, y_pred_k):.4f}")

```