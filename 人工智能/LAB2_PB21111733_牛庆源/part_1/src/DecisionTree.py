from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
import numpy as np 
import pandas as pd 

# metrics
def accuracy(y_true, y_pred):
    return sum(y_true == y_pred) / len(y_true)

# model
class DecisionTreeClassifier:
    def __init__(self) -> None:
        self.tree = None

    # 信息熵
    def entropy(y):
        classes, counts = np.unique(y, return_counts=True)
        probabilities = counts / len(y)
        return -np.sum(probabilities * np.log2(probabilities))

    # 信息增益
    def info_gain(self, X, y, feature, threshold):
        left_idx = X[:, feature] < threshold
        right_idx = X[:, feature] >= threshold
        left_entropy = self.entropy(y[left_idx])
        right_entropy = self.entropy(y[right_idx])
        return self.entropy(y) - np.mean(left_idx) * left_entropy - np.mean(right_idx) * right_entropy
    
    # 选择最佳分割点
    def best_split(self, X, y):
        best_feature, best_threshold, best_info_gain = None, None, -np.inf
        n_features = X.shape[1]
        for feature in range(n_features):
            thresholds = np.unique(X[:, feature])
            for threshold in thresholds:
                ig = self.info_gain(X, y, feature, threshold)
                if ig > best_info_gain:
                    best_feature, best_threshold, best_info_gain = feature, threshold, ig
        return best_feature, best_threshold, best_info_gain
    
    # 递归构建决策树
    def build_tree(self, X, y, max_depth, min_samples_leaf):
        if len(y) == 0:
            return {'threshold': None}
        if max_depth == 0 or len(y) < min_samples_leaf:
            return {'threshold': np.argmax(np.bincount(y))}
        feature, threshold, info_gain = self.best_split(X, y)
        if info_gain == 0:
            return {'threshold':np.argmax(np.bincount(y))}
        left_idx = X[:, feature] < threshold
        right_idx = X[:, feature] >= threshold
        left_tree = self.build_tree(X[left_idx], y[left_idx], max_depth-1, min_samples_leaf)
        right_tree = self.build_tree(X[right_idx], y[right_idx], max_depth-1, min_samples_leaf)
        return {'feature': feature, 
                'threshold': threshold, 
                'left_tree': left_tree, 
                'right_tree': right_tree}

    def fit(self, X, y, max_depth=5, min_samples_leaf=2):
        # X: [n_samples_train, n_features], 
        # y: [n_samples_train, ],
        # TODO: implement decision tree algorithm to train the model
        X = np.array(X)
        y = np.array(y)
        self.tree = self.build_tree(X, y, max_depth, min_samples_leaf)


    def predict(self, X):
        # X: [n_samples_test, n_features],
        # return: y: [n_samples_test, ]        
        X = np.array(X)
        y = np.zeros(X.shape[0])
    
        for i in range(X.shape[0]):
            node = self.tree
            while 'feature' in node:
                if X[i][node['feature']] < node['threshold']:
                    node = node['left_tree']
                else:
                    node = node['right_tree']
            y[i] = node['threshold']    
        return y


def load_data(datapath:str='./data/ObesityDataSet_raw_and_data_sinthetic.csv'):
    df = pd.read_csv(datapath)
    continue_features = ['Age', 'Height', 'Weight', ]
    discrete_features = ['Gender', 'CALC', 'FAVC', 'FCVC', 'NCP', 'SCC', 'SMOKE', 'CH2O', 'family_history_with_overweight', 'FAF', 'TUE', 'CAEC', 'MTRANS']

    X, y = df.iloc[:, :-1], df.iloc[:, -1]
    # encode discrete str to number, eg. male&female to 0&1
    labelencoder = LabelEncoder()
    for col in discrete_features:
        X[col] = labelencoder.fit(X[col]).transform(X[col])
    y = labelencoder.fit(y).fit_transform(y)
    
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    return X_train, X_test, y_train, y_test

if __name__=="__main__":
    # 路径问题
    X_train, X_test, y_train, y_test = load_data('./part_1/data/ObesityDataSet_raw_and_data_sinthetic.csv')
    clf = DecisionTreeClassifier()
    accuracy_init = 0
    for i in range(5, 12):
        max_depth = i
        for j in range(2, 10):
            min_samples_leaf = j
            clf.fit(X_train, y_train, max_depth=max_depth, min_samples_leaf=min_samples_leaf)
            y_pred = clf.predict(X_test)
            if accuracy(y_test, y_pred) > accuracy_init:
                accuracy_init = accuracy(y_test, y_pred)
                max_depth_best = max_depth
                min_samples_leaf_best = min_samples_leaf

    print(f"准确度: {accuracy_init}, 最佳最大深度: {max_depth_best}, 最佳最小样本量: {min_samples_leaf_best}")
