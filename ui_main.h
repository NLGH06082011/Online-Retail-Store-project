// Functions for user interface
// Welcome screen
void hello()
{
	// Set up ANSI ESC Code support for terminal
	ansiState = enableVTProcessing();
	if (ansiState == ENABLE_FAIL)
	{
		ansiState = startAnsicon();
		if (ansiState == ENABLE_FAIL)
		{
			cout << "Error: The program can't get ANSI ESC Code text formatting support of this terminal to work.\n";
			cout << "The program tries to either start Ansicon given that it's installed and in PATH environment variable (works with Windows 10-), or enable VT Sequence processing (Windows 10+).\n";
			cout << "Apparently, both of these failed. So if you want to proceed to using this program, then you can, but the unprocessed ANSI ESC Codes will look terrible.\n";
			system("pause");
		}
	}
	// Set up proper terminal window size
	if (!setConsoleDimensions(175, 1000, 175, 45))
	{
		cout << "Error: Problem setting up the proper terminal window dimensions for this program. If your preset dimensions are too narrow in width, some visuals may bug out because of that.\n";
		system("pause");
	}
	cout << boolalpha; // Bool alpha
	cout << left; // Correct margin
	// Set receipt writing location to CWD
	filesystem::path cwd = filesystem::current_path();
	receiptLocation = cwd.wstring();
	// Get the "red text indicates low product quantity" working
	qtyLowLimit /= productAmount;
	qtyLowLimit /= 3;
	// Welcome!
	cerr << "\033[0m";
	system("cls");
	cout << "\033[36mHello!\n";
	cout << "This is the ultimate Online Retail Store, which will drive Amazon out of business >:)\n";
	cout << "In here, you can browse the products, get their details, add them to cart, view and change your cart, search for products with filtering and sorting options, etc...\n";
	cout << "Happy shopping!\033[0m" << endl;
	system("pause");
	system("cls");	
	return;
}

// View product details
void viewProduct(product* product)
{
	// Print product details
	string buttonSelection;
	bool retryButtonSelection = false;
	system("cls");	
	cout << "\033[92mView Product: " << product->coutName() << "\n----------\n\033[31m*Red colored quantity value indicates low quantity\n\033[0m";
	cout << product->coutLabel() << "\n";
	cout << product->coutPrice() << "\n";
	cout << product->coutQty() << "\n";
	product->printDscr();
	cout << product->coutAmountBought() << endl;
	cout << "\n----------\n\n";
	// Select actions
	string promtText = "Enter amount to change to Cart (Ctrl + Z to cancel): ";
	do
	{
		buttonSelection = buttonConsole(viewProductDetails, 1, 4, 24);
		if (buttonSelection == "Change amount to Cart")
		{
			optional<int> changeAmount = promptIntInput(promtText, "Invalid, please retry: ", true);
			if (changeAmount)
			{
				if (changeAmount.value() != 0)
				{
					try
					{
						cartEdit(product, changeAmount.value());
						cout << "Changed to " << changeAmount.value() << " in Cart" << endl;
						retryButtonSelection = false;
					}
					catch (const invalid_argument& e)
					{
						cerr << "Error: " << e.what();
						retryButtonSelection = true;
					}
					Sleep(1000);
					cerr << "\033[F\033[F\033[F\r\033[J";
				}
				else
				{
					cout << "Invalid amount (select 'Delete' button to delete from Cart)" << endl;
					Sleep(1000);
					cerr << "\033[F\033[F\033[F\r\033[J";
					retryButtonSelection = true;
				}
			}
			else
			{
				cout << "Canceled" << endl;
				Sleep(1000);
				cerr << "\033[F\033[F\033[F\r\033[J";
				retryButtonSelection = true;
			}
		}
		if (buttonSelection == "Delete product from Cart")
		{
			retryButtonSelection = false;
			cartEdit(product, 0);
			cout << "Deleted from Cart" << endl;
			Sleep(1000);
			cerr << "\033[F\033[F\033[F\r\033[J";
		}
		if (buttonSelection == "Back")
		{
			return;
		}
		if (buttonSelection == "Back to Home")
		{
			throw BackToHome("");
		}
	}
	while (retryButtonSelection);
	return;
}

// Browse all products or from a list of searched products or from a list of added to Cart products
void browseProducts(bool browseCart = false, bool browseCartWithBack = false, searchOutput* productList = nullptr, string input = "", bool priceFilter = false, int min = 0, int max = 0, bool sortByPrice = false, bool sortPriceDecending = false)
{
	bool browseList = false;
    if (productList != nullptr)
    {
        browseList = true;
		if (browseCart)
		{
			throw invalid_argument("What is this?!?!??!?!?!"); // Code impossible to execute unless something is tampered with
		}
    }
    while (true)
    {
        string buttonSelection;
        bool retryButtonSelection = false;
		system("cls");       
        if (!browseList && !browseCart)
        {
            cout << "\033[91mBrowse all " << productAmount << " products\n----------\n\033[31m*Red colored quantity value indicates low quantity\n\033[0m";
        }
		else if (browseList)
        {
			cout << "\033[91mList " << searchCount << " searched product(s) | Search keyword as '" << input << "'";
			if (priceFilter)
			{
				cout << " | Price filter with min, max as $" << min << ", $" << max;
			}
			if (sortByPrice)
			{
				cout << " | Price-based sorting in " << (sortPriceDecending ? "decending order" : "ascending order");
			}
			cout << "\n----------\n\033[31m*Red colored quantity value indicates low quantity\n\033[0m";
        }
		else
		{
			cout << "\033[91mList total " << totalEntries << ((totalEntries < 2) ? " product entry added to cart" : " product entries added to cart") << "\n----------\n\033[31m*Red colored quantity value indicates low quantity\n\033[0m";
		}
        // Print products
        if (!browseList)
        {
			if (!browseCart)
			{
				for (int i = 0; i < productAmount; i++)
				{
					printListGuide = (i + 1);
					cout << productCtl[i] << "\n\n";
				}
			}
			else
			{
				for (int i = 0; i < totalEntries; i++)
				{
					printListGuide = (i + 1);
					cout << entriesList[i] << " | Total money spent: $\033[33m" << entriesList[i]->getPrice() << "\033[0m * \033[33m" << entriesList[i]->getAmountBought() 
						 << "\033[0m = $\033[33m" << 1UL * entriesList[i]->getPrice() * entriesList[i]->getAmountBought() << "\033[0m\n\n";
				}
				cout << "\033[97mTotal cost: $\033[93m" << totalPrice << "\033[0m\n" << endl;
			}
        }
        else
        {
            for (int i = 0; i < searchCount; i++)
            {
                printListGuide = (i + 1);
                cout << productList[i].id << " | Keyword occurence: \033[33m" << productList[i].occur << "\033[0m" << "\n\n";
            }
        }
        cout << "----------\n\n";
        // Select actions
        do
        {
			if (!browseList && !browseCart)
			{
				buttonSelection = buttonConsole(browseAllProducts, 1, 2, 20);
			}
			else if (browseList)
			{
				buttonSelection = buttonConsole(browseSearchedProducts, 1, 3, 20);
			}
			else
			{
				if (browseCartWithBack)
				{
					buttonSelection = buttonConsole(viewCartWithBack, 1, 4, 20);
				}
				else
				{
					buttonSelection = buttonConsole(viewCart, 1, 3, 20);
				}
			}
            if (buttonSelection == "View product details")
            {
                optional<int> viewDetail = promptIntInput("Enter number to view the corresponding product's details (Ctrl + Z to cancel): ", "Invalid, please retry: ", true);
                if (viewDetail)
                {
                    if (viewDetail.value() > 0 && viewDetail.value() <= productAmount && !browseList && !browseCart)
                    {
						retryButtonSelection = false;
						viewProduct(productCtl[viewDetail.value() - 1]);
                    }
					else if (viewDetail.value() > 0 && viewDetail.value() <= totalEntries && browseCart)
					{
						retryButtonSelection = false;
						viewProduct(entriesList[viewDetail.value() - 1]);
					}
					else if (viewDetail.value() > 0 && viewDetail.value() <= searchCount && browseList)
					{
						retryButtonSelection = false;
						viewProduct(productList[viewDetail.value() - 1].id);
					}
                    else
                    {
                        cout << "Product not exist" << endl;
                        Sleep(1000);
                        cerr << "\033[F\033[F\033[F\r\033[J";
                        retryButtonSelection = true;
                    }
                }
                else
                {
                    cout << "Canceled" << endl;
                    Sleep(1000);
                    cerr << "\033[F\033[F\033[F\r\033[J";
                    retryButtonSelection = true;
                }
            }
            if (buttonSelection == "Back to Home")
            {
                throw BackToHome("");
            }
			if (buttonSelection == "Back")
			{
				return;
			}
			if (buttonSelection == "Delete all")
			{
				string answer = promptStringInput("Are you sure you want to delete all entries in the cart? 'Y' for yes and everything else for no: ", "Invalid, please retry: ");
				if (answer == "Y" || answer == "y")
				{
					while (totalEntries != 0)
					{
						cartEdit(entriesList[0], 0);
					}
					retryButtonSelection = false;
					cout << "Deleted" << endl;
					Sleep(1000);
					return;
				}
				else
				{
					cerr << "\033[F\033[F\r\033[J";
					retryButtonSelection = true;
				}
			}
        } while (retryButtonSelection);
    }
}

// Search for products
void searchProducts()
{
	// Search settings (static variable to keep settings throughout program runtime)
	static bool priceFilter = false;
	static int min = 0;
	static int max = 0;
	static bool sortByPrice = false;
	static bool sortPriceDecending = false;
	do
	{
		// Intro + print search settings
		system("cls");
		cout << "\033[94mSearch products \n----------\033[33m";
		if (priceFilter)
		{
			cout << "\nSettings: Price filter enabled | " << "Min price: $" << min << " | Max price: $" << max;
		}
		if (sortByPrice)
		{
			if (!priceFilter)
			{
				cout << "\nSettings: Sort by price enabled: ";
			}
			else
			{
				cout << " | " << "Sort by price enabled: ";
			}
			if (sortPriceDecending)
			{
				cout << "Decending";
			}
			else
			{
				cout << "Ascending";
			}
		}
		cout << "\033[0m" << endl;
		string selection = buttonConsole(searchForProducts, 2, 4, 23);
		if (selection == "Search keyword")
		{
			string input = promptStringInput("Search for products using keywords (Ctrl + Z to cancel): ", "Invalid, please retry: ", true);
			if (input.empty())
			{
				cerr << "Canceled";
				Sleep(1000);
			}
			try
			{
				array<searchOutput, productAmount> results = searchProduct(input, priceFilter, min, max, sortByPrice, sortPriceDecending);
				browseProducts(false, false, results.data(), input, priceFilter, min, max, sortByPrice, sortPriceDecending);
			}
			catch (const invalid_argument& e)
			{
				cerr << "Error: " << e.what();
				Sleep(1000);
			}
		}
		if (selection == "Toggle price filter")
		{
			priceFilter ? priceFilter = false : priceFilter = true;
		}
		if (selection == "Change min price")
		{
			optional<int> changeMin = promptIntInput("Changing minimum price filter (Ctrl + Z to cancel): ", "Invalid, please retry: ", true);
			if (changeMin)
			{
				min = changeMin.value();
			}
			else
			{
				cout << "Canceled" << endl;
				Sleep(1000);
			}
		}
		if (selection == "Change max price")
		{
			optional<int> changeMax = promptIntInput("Changing maximum price filter (Ctrl + Z to cancel): ", "Invalid, please retry: ", true);
			if (changeMax)
			{
				max = changeMax.value();
			}
			else
			{
				cout << "Canceled" << endl;
				Sleep(1000);
			}
		}
		if (selection == "Toggle price sort")
		{
			sortByPrice ? sortByPrice = false : sortByPrice = true;
		}
		if (selection == "Change price sort order")
		{
			sortPriceDecending ? sortPriceDecending = false : sortPriceDecending = true;
		}
		if (selection == "Reset search settings")
		{
			priceFilter = false;
			min = 0;
			max = 0;
			sortByPrice = false;
			sortPriceDecending = false;
		}
		if (selection == "Back to Home")
		{
			return;
		}
	} while (true);
}

// Discount
const int randomIntsSize = 500; // Size of the discount value list
double n;
void spin(array<int, randomIntsSize>&);
void discountPrices(bool withBack = false)
{
	static int att = 5;
	while (true)
	{
		string buttonSelection;
		system("cls");
		cout << "\033[95mApply discount\n----------\n\033[93mCurrent discount: " << discount << "\033[0m%" << endl;
		cout << "You have " << att << " chance(s) left to randomly get a discount\n" << endl << "\033[1F";
		if (att == 0)
		{
			Sleep(1000);
			return;
		}
		array<int, randomIntsSize> randomInts;
		for (int i = 0; i < randomIntsSize; i++)
		{
			randomInts[i] = genRand();
		}
		if (withBack)
		{
			buttonSelection = buttonConsole(applyDiscountWithBack, 1, 3, 13);
		}
		else
		{
			buttonSelection = buttonConsole(applyDiscount, 1, 2, 13);
		}
		if (buttonSelection == "Back to Home")
		{
			throw BackToHome("");
		}
		if (buttonSelection == "Get discount!")
		{
			cout << "\033[1E";
			att--;
			spin(randomInts);
		}
		if (buttonSelection == "Back")
		{
			return;
		}
	}
}

// Spin the discount
void spin(array<int, randomIntsSize>& discountWheel)
{
	int length = genRand(true); // Length of the wheel
	n = 1000 * (1 + exp(-(length - 500) / 14));
	// All colors thanks to ChatGPT
	static const array<string, 8> colorPairs = 
	{
		"\033[1;30;47m", // Black text on White background
		"\033[1;31;46m", // Red text on Cyan background
		"\033[1;32;45m", // Green text on Magenta background
		"\033[1;33;44m", // Yellow text on Blue background
		"\033[1;34;43m", // Blue text on Yellow background
		"\033[1;35;42m", // Magenta text on Green background
		"\033[1;36;41m", // Cyan text on Red background
		"\033[1;37;40m", // White text on Black background
	};
	cout << "\n \033[0m\033[1m" << char(24) << " \033[1F";
	stringstream ss;
	int j = 7;
	for (int selectedNumber = 0; selectedNumber < length; selectedNumber++)
	{
		discount = discountWheel[selectedNumber];
		cout << "\033[0m\033[2K\033[G";
		for (int i = selectedNumber; i < (selectedNumber + 41); i++, j--)
		{
			if (j < 0)
			{
				j = 7;
			}
			ss.str("");
			ss << discountWheel[i] << "%";
			cout << colorPairs[j] << setw(4) << ss.str();
		}
		if (selectedNumber == 0)
		{
			Sleep(1500);
			continue;
		}
		Sleep(n / (1 + exp(-(selectedNumber - 500) / 14)));
	}
	cout << "\033[0m";
}

// Proceed to purchase
int proceedPurchase();

// Receipt settings to do receipting stuff
void receiptSettings();

// Purchase products
int purchaseProducts()
{
	while (true)
	{
		system("cls");
		cout << "\033[93mPurchase products\n----------\n\033[0m";
		if (totalEntries == 0)
		{
			cout << "There are no products in Cart" << endl;
			Sleep(1000);
			return 0;
		}
		cout << "There " << ((totalEntries < 2) ? "is " : "are ") << "\033[33m" << totalEntries << ((totalEntries < 2) ? "\033[0m product entry" : "\033[0m product entries") << " added to Cart\n";
		cout << "Total price: $\033[33m" << totalPrice << "\033[0m\n";
		cout << "Discount: \033[33m" << discount << "\033[0m%\n";
		finalPrice = totalPrice * (1 - discount / 100.0);
		cout << "Total price after discount: $\033[33m" << finalPrice << "\033[0m\n";
		string buttonSelection = buttonConsole(purchase, 1, 4, 14);
		if (buttonSelection == "Proceed")
		{
			int exit = proceedPurchase();
			switch (exit)
			{
			case 1:
				return 1;
			default:
				break;
			}
		}
		if (buttonSelection == "View/Edit Cart")
		{
			browseProducts(true, true);
		}
		if (buttonSelection == "Apply discount")
		{
			discountPrices(true);
		}
		if (buttonSelection == "Back to Home")
		{
			throw BackToHome("");
		}
	}
	return 0;
}

int proceedPurchase()
{
	while (true)
	{
		system("cls");
		cout << "\033[93mProceed to purchasing\n----------\n\033[0m";
		cout << "Write receipt: " << (writeReceipt ? "True\n" : "False\n");
		if (writeReceipt)
		{
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << L"Receipt directory: " << receiptLocation << L"\n";
			_setmode(_fileno(stdout), _O_TEXT);
			cout << "File name is fixed to 'ORS Receipt.rtf', if there's an existing file with the same name, it will be \033[91moverwritten\033[0m\n";
		}
		string buttonSelection;
		buttonSelection = buttonConsole(proceedToPurchase, 1, 4, 16);
		if (buttonSelection == "Purchase")
		{
			bool openReceiptAfterClosing = false;
			bool fileWriteSuccess = true;
			if (writeReceipt)
			{
				cout << endl;
				string answer = promptStringInput("Do you want to automatically open the receipt after the program closes? ('Y' for yes and everything else for no): ", "Invalid, please retry: ");
				if (answer == "Y" || answer == "y")
				{
					openReceiptAfterClosing = true;
				}
			}
			cout << "\n----------\n\n\033[93m";
			int waitTime = 0;
			while (waitTime < 5)
			{
				waitTime = genRand(true) % 32;
			}
			for (int i = 0; i < waitTime; i++)
			{
				if (i < (waitTime / 4))
				{
					cout << "Starting purchase operation";
				}
				else if (i < (waitTime / 4 * 2))
				{
					cout << "Verifying credentials";
				}
				else if (i < (waitTime / 4 * 3))
				{
					cout << "Processing purchase order";
				}
				else
				{
					cout << "Finnishing up";
				}
				for (int j = 0; j < (i % 4); j++)
				{
					cout << ".";
				}
				Sleep(1000);
				cout << "\033[2K\r";
			}
			cout << "Done!\n";
			if (writeReceipt)
			{
				fileWriteSuccess = writeToReceipt();
			}
			if (writeReceipt && fileWriteSuccess)
			{
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << L"Receipt saved to " << receiptLocation << endl;
				_setmode(_fileno(stdout), _O_TEXT);
			}
			else if (writeReceipt && !fileWriteSuccess)
			{
				cout << "\033[91mError: Receipt writing failed\033[93m\n";
			}
			cout << "Thanks for shopping and goodbye!\n";
			revertTerminalSetting();
			system("@echo off");
			system("set /p=\"Press any key to exit program...\" <nul & pause >nul");
			cout << "\n\033[0mGoodbye!\n";
			Sleep(1000);
			if (writeReceipt && fileWriteSuccess && openReceiptAfterClosing)
			{
				ShellExecuteW(NULL, L"open", receiptLocation.c_str(), NULL, NULL, SW_SHOWNORMAL);
			}
			return 1;
		}
		if (buttonSelection == "Receipt settings")
		{
			receiptSettings();
		}
		if (buttonSelection == "Back")
		{
			return 0;
		}
		if (buttonSelection == "Back to Home")
		{
			throw BackToHome("");
		}
	}
}

void receiptSettings()
{
	while (true)
	{
		system("cls");
		cout << "\033[93mReceipt settings\n----------\n\033[0m";
		cout << "Write receipt: " << (writeReceipt ? "True\n" : "False\n");
		if (writeReceipt)
		{
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << L"Receipt directory: " << receiptLocation << L"\n";
			_setmode(_fileno(stdout), _O_TEXT);
			cout << "File name is fixed to 'ORS Receipt.rtf', if there's an existing file with the same name, it will be \033[91moverwritten\033[0m\n";
		}
		string buttonSelection;
		buttonSelection = buttonConsole(writeReceiptSettings, 2, 3, 32);
		if (buttonSelection == "Toggle writing receipt")
		{
			switch (writeReceipt)
			{
			case true:
				writeReceipt = false;
				break;
			default:
				writeReceipt = true;
				break;
			}
		}
		if (buttonSelection == "Save receipt to default location")
		{
			filesystem::path cwd = filesystem::current_path();
			receiptLocation = cwd.wstring();
		}
		if (buttonSelection == "Save receipt to program location")
		{
			receiptLocation = filesystem::path(getExePath()).parent_path().wstring();
		}
		if (buttonSelection == "Save receipt to custom location")
		{
			wstring pickedFolder = selectFolder();
			if (!pickedFolder.empty())
			{
				receiptLocation = pickedFolder;
			}
		}
		if (buttonSelection == "Back")
		{
			return;
		}
		if (buttonSelection == "Back to Home")
		{
			throw BackToHome("");
		}
	}
}

// Actions panel
void homeActionsPanel()
{
	while (true)
	{
		system("cls");		
		cout << "\033[96mActions Panel\n----------\n\033[0m";
		try
		{
			string selection = buttonConsole(actionsPanel, 2, 3, 19);
			if (selection == "Browse all products")
			{
				browseProducts();
			}
			if (selection == "Search products")
			{
				searchProducts();
			}
			if (selection == "View/Edit Cart")
			{
				browseProducts(true);
			}
			if (selection == "Apply discount")
			{
				discountPrices();
			}
			if (selection == "Purchase")
			{
				int exitCode = purchaseProducts();
				if (exitCode == 1)
				{
					return;
				}
			}
			if (selection == "Quit program")
			{
				string answer = promptStringInput("Are you sure you want to quit the program? You will lose all data ('Y' for yes and everything else for no): ", "Invalid, please retry: ");
				if (answer == "Y" || answer == "y")
				{
					cout << "Goodbye!\n";
					revertTerminalSetting();
					Sleep(1000);
					return;
				}
			}
		}
		catch(const BackToHome&)
		{
			continue;
		}
	}
}