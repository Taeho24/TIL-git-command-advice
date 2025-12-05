# Shuffle_Algorith
# 배열을 균일한 확률로 무작위 섞기 위한 알고리즘

'''
import random

arr = [1, 2, 3, 4, 5]
shuffled = sorted(arr, key=lambda x: random.random() - 0.5)

print(shuffled)
'''
# ! 균일 분포가 아니기 때문에 잘못된 셔플

# Fisher-Yates 셔플 알고리즘 or Knuth Shuffle(너스 셔플)
"""
길이 N의 배열을 뒤에서부터 하나씩 무작위 원소와 교환하며 섞는다.
모든 순열이 동일한 확률(1/N!) 로 나타나는 올바른 셔플 방식.

1. 배열의 마지막 인덱스 i = n−1 부터 시작
2. 0 이상 i 이하의 정수 j 를 무작위로 선택
3. A[i] 와 A[j] 를 교환
4. i = i−1 로 감소시키며 반복

시간 복잡도: O(N)
추가 메모리: O(1) (제자리 셔플)
"""
import random

def fisher_yates_shuffle(original_list):
    # 슬라이싱으로 얕은 복사 (slice()와 동일한 효과)
    arr = original_list[:]

    # 뒤에서부터 앞으로 이동하면서 랜덤 swap
    for i in range(len(arr) - 1, 0, -1):
        j = random.randint(0, i)  # 0 ~ i 사이의 정수
        arr[i], arr[j] = arr[j], arr[i]
    
    return arr


"""js code (not python)
export function shuffle<T>(originalArray: T[]): T[] {
  // slice()로 원본 배열을 얕은 복사
  const array = originalArray.slice();

  let currentIndex = array.length;
  let randomIndex;

  // While there remain elements to shuffle.
  while (currentIndex !== 0) {
    // Pick a remaining element.
    randomIndex = Math.floor(Math.random() * currentIndex);
    currentIndex--;

    // And swap it with the current element.
    [array[currentIndex], array[randomIndex]] = [
      array[randomIndex],
      array[currentIndex],
    ];
  }

  return array; // 새로운 배열 반환 (원본 불변)
}
"""

# 정렬 기반 랜덤 셔플(sort key=random)과 Fisher–Yates(random.shuffle)의 편향 차이
import random
from collections import Counter
from itertools import permutations
import matplotlib.pyplot as plt

def simulate_shuffle(arr, trials=100000):
    perms = list(permutations(arr))
    
    # 정렬 기반 랜덤 셔플
    counter_sort = Counter()
    for _ in range(trials):
        shuffled = arr[:]
        shuffled.sort(key=lambda x: random.random() - 0.5)
        counter_sort[tuple(shuffled)] += 1

    # Fisher–Yates
    counter_fy = Counter()
    for _ in range(trials):
        shuffled = arr[:]
        random.shuffle(shuffled)
        counter_fy[tuple(shuffled)] += 1
    
    # 데이터 준비
    counts_sort = [counter_sort[p] for p in perms]
    counts_fy = [counter_fy[p] for p in perms]
    labels = [str(p) for p in perms]

    # 그래프 그리기
    x = range(len(perms))
    width = 0.35

    plt.figure(figsize=(20,6))
    plt.bar([i - width/2 for i in x], counts_sort, width=width, color='skyblue', label='sort(key=random)')
    plt.bar([i + width/2 for i in x], counts_fy, width=width, color='salmon', label='random.shuffle')
    plt.xticks(x, labels, rotation=90)
    plt.ylabel('Count')
    plt.title(f'Permutation Distribution for array of size {len(arr)} over {trials} Trials')
    plt.legend()
    plt.show()

# 배열 크기 5
simulate_shuffle([1,2,3,4,5], trials=100000)
