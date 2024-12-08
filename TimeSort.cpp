#include <iostream>
#include <cstddef>
#include <cstdlib>

int calcMinrun(int size) {
	//Если массив меншье 64 - деление не требуется
	if (size < 64) return size;

	//Делим размер исходного массива на 2, пока он не станет меньше 64
	int r = 0;
	while (size > 64)
	{
		r |= size & 1;
		size >>= 1;
	}

	return size + r;
}

void printArray(int* data, size_t size) {

	for (int i = 0;i < size;i++) {
		std::cout << data[i] << ' ';
	}
	std::cout << std::endl << std::endl;
}

void insertSort(int* data, int size) {

	int i, key, j;
	for (i = 1; i < size; i++) {
		key = data[i];
		j = i - 1;

		// Перемещаем элементы arr[0..i-1], которые больше key, на одну позицию вперед
		while (j >= 0 && data[j] > key) {
			data[j + 1] = data[j];
			j = j - 1;
		}
		data[j + 1] = key;
	}

}


void merge(int data[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Временные массивы
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	for (int i = 0; i < n1; i++)
		L[i] = data[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = data[mid + 1 + j];

	// Объеденяем временные массивы
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			data[k] = L[i];
			i++;
		}
		else {
			data[k] = R[j];
			j++;
		}
		k++;
	}

	// Копируем оставшиеся элементы L[]
	while (i < n1) {
		data[k] = L[i];
		i++;
		k++;
	}

	// Копируем оставшиеся элементы  R[]
	while (j < n2) {
		data[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}

void timeSort(int* data, int size, int minrun) {

	//сортировка подмассивов вставкой 
	for (int i = 0; i < size; i += minrun) {
		std::cout << "Сортируем подмассив с позиции: " << i << " длинной:" << std::min<int>(minrun, size - i) << std::endl;
		insertSort(&data[i], std::min(minrun, size - i));
	}

	//Сортировка методом объединения
	for (int n = minrun; n < size; n *= 2) {
		for (int left = 0; left < size; left += 2 * n) {
			int mid = left + n - 1;
			int right = std::min(left + 2 * n - 1, size - 1);

			// Merge arr[left..mid] and arr[mid+1..right]
			if (mid < right)
				merge(data, left, mid, right);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "");
	int size;
	std::cout << "Введите число элементов" << std::endl << "> ";
	std::cin >> size;


	int* data = (int*)malloc(sizeof(int) * (size + 1));

	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		data[i] = rand() % 1000;
	}
	std::cout << "Начальный массив:" << std::endl;
	printArray(data, size);


	int minrun = calcMinrun(size);
	std::cout << "minRUN:" << minrun << std::endl;

	//Сортировка
	timeSort(data, size, minrun);


	//timsort(vec, minrun);
	std::cout << "Отсоритированный массив:" << std::endl;
	printArray(data, size);


	free(data);

	return 0;
}