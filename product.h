// Product class to store info about a product
extern const int productAmount = 223; // Total amount of products
class product; // Pre-declare so I can define productCtl
extern array<product*, productAmount> productCtl = {}; // ID catalog, also can be called as "product catalog"
extern int qtyLowLimit = 0; // If a qty of a product is below this -> Low quantity warning

// Product class for a product info when browsing products
class product
{
private:
	// Note: Product ID is in the productCtl so no ID var needed here
	int price; // Price
	int qty; // Amount in stock
	int amountBought; // How many of this product was added to cart
	string name; // Product name
	string dscr; // Product description
	static int currentProductNo; // Used to set values in product catalog

public:
	// Object initialization and registeration to product catalog
	product(string enterName, int enterPrice, int enterQty, string enterDscr)
	{
		amountBought = 0;
		name = enterName;
		price = enterPrice;
		qty = enterQty;
		qty *= 137;
		qtyLowLimit += qty;
		productCtl[currentProductNo] = this;
		currentProductNo++;
		dscr = enterDscr;
	}

public:
	// Get functions
	string getFullName()
	{
		return name;
	}
	string coutName()
	{
		// Get name but not the () part
		int tmp = 0;
		// Get location of the '('
		for (size_t i = 0; i < name.length(); i++)
		{
			if ('(' == name[i])
			{
				tmp = i;
				break;
			}
		}
		return name.substr(0, --tmp);
	}

	string coutLabel()
	{
		// Get the () part
		int tmp = 0;
		// Get location of the '('
		for (size_t i = 0; i < name.length(); i++)
		{
			if ('(' == name[i])
			{
				tmp = i;
				break;
			}
		}
		return string("Label: \033[33m") + name.substr(++tmp, (name.length() - tmp - 2)) + string("\033[0m");
	}

	string coutQty()
	{
		stringstream text;
		if (qty < qtyLowLimit)
		{
			text << "\033[31m" << qty << "\033[0m in stock";
		}
		else
		{
			text << "\033[33m" << qty << "\033[0m in stock";
		}
		return text.str();
	}

	int getQty()
	{
		return qty;
	}

	string coutPrice()
	{
		stringstream text;
		text << "Price: $\033[33m" << price << "\033[0m";
		return text.str();
	}

	int getPrice()
	{
		return price;
	}

	int getAmountBought()
	{
		return amountBought;
	}

	string coutAmountBought()
	{
		stringstream text;
		text << "Amount added to cart: \033[33m" << amountBought << "\033[0m";
		return text.str();
	}

	void printDscr()
	{
		cout << "Description: \033[33m" << dscr << "\033[0m" << endl;
		return;
	}

	void setAmountToCart(int amount)
	{
		amountBought = amount;
		return;
	}
};

int product::currentProductNo = 0;