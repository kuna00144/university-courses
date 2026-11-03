import pandas as pd
import numpy as np
import os

os.environ.setdefault("MPLCONFIGDIR", ".matplotlib-cache")
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from sklearn import svm
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

# Mac에서 한글 깨짐 방지
plt.rcParams["font.family"] = "AppleGothic"
plt.rcParams["axes.unicode_minus"] = False

# 데이터 읽기
df = pd.read_csv("gym_members_exercise_tracking.csv")

# Calories_Burned를 기준으로 운동 강도 라벨 생성
df["Workout_Intensity"] = pd.qcut(
    df["Calories_Burned"],
    q=3,
    labels=["낮은 강도", "적정 강도", "고강도"]
)

# 입력 특징과 정답 레이블 분리
# Calories_Burned는 라벨 생성에 사용했으므로 입력에서 제외
X = df[
    [
        "Age",
        "Gender",
        "Weight (kg)",
        "Height (m)",
        "Max_BPM",
        "Avg_BPM",
        "Resting_BPM",
        "Session_Duration (hours)",
        "Workout_Type",
        "Fat_Percentage",
        "Water_Intake (liters)",
        "Workout_Frequency (days/week)",
        "Experience_Level",
        "BMI"
    ]
]

y = df["Workout_Intensity"]

# 범주형 특징 원핫 인코딩
X = pd.get_dummies(X, columns=["Gender", "Workout_Type"])
X = X.astype(float)

# 훈련 집합과 테스트 집합 분할
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0, stratify=y)

# 수치형 특징 표준화
num_cols = [
    "Age",
    "Weight (kg)",
    "Height (m)",
    "Max_BPM",
    "Avg_BPM",
    "Resting_BPM",
    "Session_Duration (hours)",
    "Fat_Percentage",
    "Water_Intake (liters)",
    "Workout_Frequency (days/week)",
    "Experience_Level",
    "BMI"
]

scaler = StandardScaler()
X_train = X_train.copy()
X_test = X_test.copy()
X_train[num_cols] = scaler.fit_transform(X_train[num_cols])
X_test[num_cols] = scaler.transform(X_test[num_cols])

# SVM 모델 학습 및 예측
model = svm.SVC(kernel="rbf", C=10, gamma=0.01)

model.fit(X_train, y_train)
y_pred = model.predict(X_test)

# 정확도
accuracy = accuracy_score(y_test, y_pred)

print("===== SVM 테스트 결과 =====")
print("정확도:", accuracy)

# 혼동 행렬
labels = ["낮은 강도", "적정 강도", "고강도"]

cm = confusion_matrix(
    y_test,
    y_pred,
    labels=labels
)

cm_df = pd.DataFrame(
    cm,
    index=[f"실제_{label}" for label in labels],
    columns=[f"예측_{label}" for label in labels]
)

print("\n===== 혼동 행렬 =====")
print(cm_df)

# 혼동 행렬 이미지 저장
fig, ax = plt.subplots(figsize=(6, 5))

im = ax.imshow(cm, cmap="Blues")

ax.set_title("혼동 행렬", fontsize=16, fontweight="bold")
ax.set_xlabel("예측 강도", fontsize=12)
ax.set_ylabel("실제 강도", fontsize=12)

ax.set_xticks(np.arange(len(labels)))
ax.set_yticks(np.arange(len(labels)))

ax.set_xticklabels(labels)
ax.set_yticklabels(labels)

ax.xaxis.set_label_position("top")
ax.xaxis.tick_top()

threshold = cm.max() / 2

for i in range(len(labels)):
    for j in range(len(labels)):
        text_color = "white" if cm[i, j] > threshold else "black"
        ax.text(
            j,
            i,
            cm[i, j],
            ha="center",
            va="center",
            fontsize=16,
            color=text_color
        )

fig.colorbar(im, ax=ax)
plt.tight_layout()
plt.savefig("confusion_matrix.png", dpi=300)
plt.close(fig)

# 클래스별 민감도와 특이도
metrics = []
total = cm.sum()

for i, label in enumerate(labels):
    TP = cm[i, i]
    FN = cm[i, :].sum() - TP
    FP = cm[:, i].sum() - TP
    TN = total - TP - FN - FP

    sensitivity = TP / (TP + FN) if (TP + FN) != 0 else 0
    specificity = TN / (TN + FP) if (TN + FP) != 0 else 0

    metrics.append({
        "category": label,
        "TP": TP,
        "FN": FN,
        "FP": FP,
        "TN": TN,
        "민감도(Sensitivity)": sensitivity,
        "특이도(Specificity)": specificity
    })

metrics_df = pd.DataFrame(metrics)

print("\n===== 클래스별 민감도 / 특이도 =====")
print(metrics_df)

# 분류 리포트
print("\n===== 분류 리포트 =====")
print(classification_report(
    y_test,
    y_pred,
    labels=labels,
    target_names=labels,
    zero_division=0
))

# 오분류 사례 일부
result_df = pd.DataFrame({
    "실제 운동 강도": y_test.values,
    "예측 운동 강도": y_pred
})

wrong_df = result_df[result_df["실제 운동 강도"] != result_df["예측 운동 강도"]]

print("\n===== 오분류 사례 일부 =====")
print(wrong_df.head(10))

# 5겹 교차 검증
cv_model = make_pipeline(
    StandardScaler(),
    svm.SVC(kernel="rbf", C=10, gamma=0.01)
)

cv_scores = cross_val_score(cv_model, X, y, cv=5)

print("\n===== 5겹 교차 검증 결과 =====")
print("각 fold 정확도:", cv_scores)
print("평균 정확도:", cv_scores.mean())
print("정확도 표준편차:", cv_scores.std())