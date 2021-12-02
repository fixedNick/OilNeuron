#include "Fossil.h"

Fossil::Fossil() {}
Fossil::Fossil(string _name) {
	name = _name;
}

void Fossil::add_neuron(Neuron n)
{
	neurons.push_back(n);
}

bool Fossil::is_digged_fossil_is_equal_this_fossil(DigFossil digged_fossil)
{
	auto digged_fossil_elements = digged_fossil.get_elements();
	int digged_fossil_elements_count = digged_fossil.get_elements_count();

	for(int i = 0; i < digged_fossil_elements_count; i++)
	{
		// Если после цикла j<neurons.size() -> isElementRecognized не станет true, 
		// значит один из элементов выкопанного ископаемого не был распознан
		// дальше распозновать нет смысла - возвращаем false, это не наше ископаемое, которое мы ищем
		bool isElementRecognized = false; 
		for (int j = 0; j < neurons.size(); j++)
		{
			isElementRecognized = neurons[j].recognize(digged_fossil_elements[i]);
			if (isElementRecognized) // Распознали элемент, переходим к следующему распознаванию
				break;
		}
		// При распозновании последнего элемента если не сработает это условие(то есть мы распознаем все элементы)
		// значит мы распознали последний элемент успешно(как и все предыдущие) - мы выйдем из цикла и метод вернет TRUE
		if (isElementRecognized == false) 
			return false;
	}
	return true;
}
