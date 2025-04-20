// Search and filter functions

// Convert strings to lower case thanks to ChatGPT
std::string toLower(const std::string& str) {
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

extern int searchCount = 0; // To help indicate browse product function how many products are in the searched list

struct searchOutput
{
	product* id; // ID of product
	int occur; // How many keywords are found in the name
	searchOutput() // Set ID to NULL by default
		: id(nullptr)
	{}
};

array<searchOutput, productAmount> sortOutput(array<searchOutput, productAmount>);
array<searchOutput, productAmount> sortOutput(array<searchOutput, productAmount>, bool);

// Search algorithm
array<searchOutput, productAmount> searchProduct(string keyword, bool priceFilter = false, int min = 0, int max = 0, bool sortByPrice = false, bool sortPriceDecending = false)
{
	if (keyword.empty())
	{
		throw invalid_argument("Keyword for search is empty\n");
	}
	if (min < 0 || max < 0 || min > max)
	{
		throw invalid_argument("Min and/or max value(s) is invalid\n");
	}
	array<searchOutput, productAmount> output;
	int outputCount = 0;
	// Search through all products
	for (int i = 0; i < productAmount; i++)
	{
		if (priceFilter)
		{
			if (productCtl[i]->getPrice() < min || productCtl[i]->getPrice() > max)
			{
			continue;
			}
		}
		int occur = 0;
		string name = productCtl[i]->getFullName();
		size_t lastPosFound = (toLower(name)).find(toLower(keyword));
		if (lastPosFound == string::npos)
		{
			continue;
		}
		do
		{
			occur++;
			lastPosFound = (toLower(name)).find(toLower(keyword), lastPosFound + keyword.length());
		} while (lastPosFound != string::npos);
		output[outputCount].id = productCtl[i];
		output[outputCount].occur = occur;
		outputCount++;
	}
	searchCount = outputCount;
	// Search done with counts of how many keywords are found in one name with/without price filter
	// Now sort them in decending order or either decending or acending with price sort
	if (!sortByPrice)
	{
		output = sortOutput(output);
	}
	else if (sortPriceDecending)
	{
		output = sortOutput(output, true);
	}
	else
	{
		output = sortOutput(output, false);
	}
	return output;
}

// Normal decending sort with no price sort
array<searchOutput, productAmount> sortOutput(array<searchOutput, productAmount> output)
{
	for (int i = 0; i < productAmount - 1; i++)
	{
		for (int j = 0; j < productAmount - i - 1; j++)
		{
			if (output[j].id == nullptr || (output[j + 1].id != nullptr && output[j].occur < output[j + 1].occur))
			{
				swap(output[j], output[j + 1]);
			}
		}
	}
	return output;
}

//Price sort decending/acending
array<searchOutput, productAmount> sortOutput(array<searchOutput, productAmount> output, bool sortPriceDecending)
{
	for (int i = 0; i < productAmount - 1; i++)
	{
		for (int j = 0; j < productAmount - i - 1; j++)
		{
			if (output[j].id == nullptr || (output[j + 1].id != nullptr && output[j].id->getPrice() < output[j + 1].id->getPrice() && sortPriceDecending))
			{
				swap(output[j], output[j + 1]);
				continue;
			}
			else if (output[j + 1].id != nullptr && output[j].id->getPrice() > output[j + 1].id->getPrice() && !sortPriceDecending)
			{
				swap(output[j], output[j + 1]);
			}
		}
	}
	return output;
}