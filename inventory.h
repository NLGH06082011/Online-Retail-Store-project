// Code for a shopping cart basically
// Some variables and an array needed
extern unsigned int totalEntries = 0; // Amount of product entries added to cart
extern unsigned int totalProductAmount = 0; // How many products are added to cart
extern unsigned long int totalPrice = 0; // Total price
extern array<product*, productAmount> entriesList = {}; // List of product IDs in cart
extern int discount = 0; // Price discount
extern unsigned int finalPrice = 0; // Final price when total price is applied with price discount

// Cart
void deleteEntry(product*);
void newEntry(product*, int);
void changeEntry(product*, int);

// Request an addition/deletion/change of a product entry in cart
void cartEdit(product* id, int targetAmount)
{
	switch (id->getAmountBought())
	{
	case 0:
		newEntry(id, targetAmount);
		return;
	default:
		changeEntry(id, targetAmount);
		return;
	}
}

// Change a product entry
void changeEntry(product* id, int amount)
{
	// If a deletion is requested (product amount is set to 0), do the deletion
	if (amount == 0)
	{
		deleteEntry(id);
		return;
	}
	// If requested a negative amount
	if (amount < 0)
	{
		throw invalid_argument("Can't order negative amount of products\n");
	}
	// Change product amount (change entry)
	if (id->getQty() < amount)
	{
		// Yeah you can't order more than what's available in stock
		throw invalid_argument("Can't order more products than what's available in stock\n");
	}
	totalProductAmount -= id->getAmountBought();
	totalPrice -= id->getAmountBought() * id->getPrice();
	id->setAmountToCart(amount);
	totalProductAmount += amount;
	totalPrice += amount * id->getPrice();
	return;
}

// New entry
void newEntry(product* id, int amount)
{
	if (id->getQty() < amount)
	{
		// Yep still can't order more than what's available in stock
		throw invalid_argument("Can't order more products than what's available in stock\n");
	}
	// Same for negative requests
	if (amount < 0)
	{
		throw invalid_argument("Can't order negative amount of products\n");
	}
	id->setAmountToCart(amount);
	entriesList[totalEntries] = id;
	totalEntries++;
	totalProductAmount += amount;
	totalPrice += amount * id->getPrice();
	return;
}

// Delete entry
void deleteEntry(product* id)
{
	totalPrice -= id->getAmountBought() * id->getPrice();
	totalProductAmount -= id->getAmountBought();
	id->setAmountToCart(0);
	for (int i = 0; i < totalEntries; i++)
	{
		if (entriesList[i] == id)
		{
			entriesList[i] = nullptr;
			for (int back = (i + 1), front = i; back < totalEntries; back++, front++)
			{
				swap(entriesList[front], entriesList[back]);
			}
		}
	}
	totalEntries--;
	return;
}