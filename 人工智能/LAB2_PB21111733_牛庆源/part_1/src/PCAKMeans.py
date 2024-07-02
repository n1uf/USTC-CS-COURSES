from sklearn.datasets import load_wine
import numpy as np 
import matplotlib.pyplot as plt
from gensim.models import KeyedVectors


def get_kernel_function(kernel):
    if kernel == "rbf":
        def rbf_kernel(x, y, gamma=1.0):
            return np.exp(-gamma * np.linalg.norm(x - y) ** 2)
        return rbf_kernel
    elif kernel == "linear":
        def linear_kernel(x, y):
            return np.dot(x, y)
        return linear_kernel
    else:
        raise ValueError("Unsupported kernel")

class PCA:
    def __init__(self, n_components: int = 2, kernel: str = "rbf") -> None:
        self.n_components = n_components
        self.kernel_f = get_kernel_function(kernel)
        self.K = None
        self.eigenvectors = None
        self.eigenvalues = None

    def fit(self, X: np.ndarray):
        # X: [n_samples, n_features]
        n_samples = X.shape[0]
        K = np.zeros((n_samples, n_samples))

        for i in range(n_samples):
            for j in range(n_samples):
                K[i, j] = self.kernel_f(X[i], X[j])

        # 中心化
        one_n = np.ones((n_samples, n_samples)) / n_samples
        K_centered = K - one_n @ K - K @ one_n + one_n @ K @ one_n
        self.K = K_centered

        # Eigenvalue decomposition
        eigenvalues, eigenvectors = np.linalg.eig(K_centered)
        idx = eigenvalues.argsort()[::-1]

        self.eigenvectors = eigenvectors[:, idx[:self.n_components]]
        self.eigenvalues = eigenvalues[idx[:self.n_components]]

    def transform(self, X: np.ndarray):
        # X: [n_samples, n_features]
        self.fit(X)
        X_reduced = (self.K @ self.eigenvectors) / np.sqrt(self.eigenvalues[:self.n_components])
        return X_reduced

class KMeans:
    def __init__(self, n_clusters:int=3, max_iter:int=10) -> None:
        self.k = n_clusters
        self.max_iter = max_iter
        self.centers = None
        self.labels = None

    # Randomly initialize the centers
    def initialize_centers(self, points):
        # points: (n_samples, n_dims,)
        n, d = points.shape

        self.centers = np.zeros((self.k, d))
        for k in range(self.k):
            # use more random points to initialize centers, make kmeans more stable
            random_index = np.random.choice(n, size=10, replace=False)
            self.centers[k] = points[random_index].mean(axis=0)
        
        return self.centers
    
    # Assign each point to the closest center
    def assign_points(self, points):
        # points: (n_samples, n_dims,)
        # return labels: (n_samples, )
        n_samples = points.shape
        self.labels = np.zeros(n_samples, dtpe = int)
        # TODO: Compute the distance between each point and each center
        # and Assign each point to the closest center
        for i in range(n_samples):
            distances = np.linalg.norm(points[i] - self.centers, axis=1)
            self.labels[i] = np.argmin(distances)
        return self.labels

    # Update the centers based on the new assignment of points
    def update_centers(self, points):
        # points: (n_samples, n_dims,)
        # TODO: Update the centers based on the new assignment of points
        for i in range(self.k):
            cluster_points = points[self.labels == i]
            if len(cluster_points) > 0:
                self.centers[i] = cluster_points.mean(axis=0)
            else:
                self.centers[i] = points[np.random.choice(len(points))]

    # k-means clustering
    def fit(self, points):
        # points: (n_samples, n_dims,)
        # TODO: Implement k-means clustering
        self.centers = self.initialize_centers(points)
        for _ in range(self.max_iter):
            previous_centers = self.centers.copy()
            self.labels = self.assign_points(points)
            self.update_centers(points)
            if np.allclose(previous_centers, self.centers):
                break

    # Predict the closest cluster each sample in X belongs to
    def predict(self, points):
        # points: (n_samples, n_dims,)
        # return labels: (n_samples, )
        return self.assign_points(points)
    
def load_data():
    words = [
        'computer', 'laptop', 'minicomputers', 'PC', 'software', 'Macbook',
        'king', 'queen', 'monarch','prince', 'ruler','princes', 'kingdom', 'royal',
        'man', 'woman', 'boy', 'teenager', 'girl', 'robber','guy','person','gentleman',
        'banana', 'pineapple','mango','papaya','coconut','potato','melon',
        'shanghai','HongKong','chinese','Xiamen','beijing','Guilin',
        'disease', 'infection', 'cancer', 'illness', 
        'twitter', 'facebook', 'chat', 'hashtag', 'link', 'internet',
    ]
    w2v = KeyedVectors.load_word2vec_format('./part_1/data/GoogleNews-vectors-negative300.bin', binary = True)
    vectors = []
    for w in words:
        vectors.append(w2v[w].reshape(1, 300))
    vectors = np.concatenate(vectors, axis=0)
    return words, vectors

if __name__=='__main__':
    words, data = load_data()
    pca = PCA(2, "linear")
    pca.fit(data)
    data_pca = pca.transform(data)

    kmeans = KMeans(n_clusters=7)
    kmeans.fit(data_pca)
    clusters = kmeans.predict(data_pca)

    # plot the data
    
    plt.figure()
    plt.scatter(data_pca[:, 0], data_pca[:, 1], c=clusters)
    for i in range(len(words)):
        plt.annotate(words[i], data_pca[i, :]) 
    plt.title("PB21111733")
    plt.savefig("PCA_KMeans.png")