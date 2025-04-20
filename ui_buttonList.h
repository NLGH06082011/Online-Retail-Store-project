// Store button lists for button navigation of each UI function

 // Default Back and Back to home (1 row 2 columns 12 setW)
array<array<buttonConsoleCell, 4>, 3> classicBacks =
{{
	{{{"Back", "\033[35m"}, {"Back to Home", "\033[36m"}, {}, {}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
}};

// Browse all products (1 row 2 columns 20 setW)
array<array<buttonConsoleCell, 4>, 3> browseAllProducts =
{ {
	{{{"View product details", "\033[34m"}, {"Back to Home", "\033[36m"}, {}, {}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
} };

// Browse list of products added to cart (1 row 3 columns 20 setW)
array<array<buttonConsoleCell, 4>, 3> viewCart =
{ {
	{{{"View product details", "\033[34m"}, {"Delete all", "\033[31m"}, {"Back to Home", "\033[36m"}, {}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
} };

// Browse list of products added to cart plus "Back" button (1 row 4 columns 20 setW)
array<array<buttonConsoleCell, 4>, 3> viewCartWithBack =
{ {
	{{{"View product details", "\033[34m"}, {"Delete all", "\033[31m"}, {"Back", "\033[35m"}, {"Back to Home", "\033[36m"}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
} };

// Browse list of searched product (1 row 3 columns 20 setW)
array<array<buttonConsoleCell, 4>, 3> browseSearchedProducts =
{ {
	{{{"View product details", "\033[34m"}, {"Back", "\033[35m"}, {"Back to Home", "\033[36m"}, {}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
} };

// View product details (1 row 4 columns 24 setW)
array<array<buttonConsoleCell, 4>, 3> viewProductDetails =
{ {
	{{{"Change amount to Cart", "\033[34m"}, {"Delete product from Cart", "\033[31m"}, {"Back", "\033[35m"}, {"Back to Home", "\033[36m"}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
} };

// Actions Panel (2 rows 3 columns 19 setW)
array<array<buttonConsoleCell, 4>, 3> actionsPanel =
{ {
	{{{"Browse all products", "\033[35m"}, {"Search products", "\033[34m"}, {"View/Edit Cart", "\033[32m"}, {}}},
	{{{"Apply discount", "\033[36m"}, {"Purchase", "\033[33m"}, {"Quit program", "\033[31m"}, {}}},
	{{{}, {}, {}, {}}},
} };

// Search products (2 rows 4 columns 23 setW)
array<array<buttonConsoleCell, 4>, 3> searchForProducts =
{ {
	{{{"Search keyword", "\033[38;5;173m"}, {"Toggle price filter", "\033[32m"}, {"Change min price", "\033[36m"}, {"Change max price", "\033[34m"}}},
	{{{"Toggle price sort", "\033[35m"}, {"Change price sort order", "\033[33m"}, {"Reset search settings", "\033[39m"}, {"Back to Home", "\033[31m"}}},
	{{{}, {}, {}, {}}},
} };

// Apply discount (1 row 2 columns 13 setW)
array<array<buttonConsoleCell, 4>, 3> applyDiscount =
{ {
	{{{"Get discount!", "\033[35m"}, {"Back to Home", "\033[32m"}, {}, {}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
} };

// Apply discount with "Back" button (1 row 3 columns 13 setW)
array<array<buttonConsoleCell, 4>, 3> applyDiscountWithBack =
{ {
	{{{"Get discount!", "\033[35m"}, {"Back", "\033[33m"}, {"Back to Home", "\033[32m"}, {}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
} };

// Purchase products (1 row 4 columns 14 setW)
array<array<buttonConsoleCell, 4>, 3> purchase =
{ {
	{{{"Proceed", "\033[33m"}, {"View/Edit Cart", "\033[35m"}, {"Apply discount", "\033[34m"}, {"Back to Home", "\033[31m"}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
} };

// Proceed to purchase (1 row 4 columns 16 setW)
array<array<buttonConsoleCell, 4>, 3> proceedToPurchase =
{ {
	{{{"Purchase", "\033[33m"}, {"Receipt settings", "\033[35m"}, {"Back", "\033[32m"}, {"Back to Home", "\033[31m"}}},
	{{{}, {}, {}, {}}},
	{{{}, {}, {}, {}}},
} };

// Receipt settings (2 row 3 columns 32 setW)
array<array<buttonConsoleCell, 4>, 3> writeReceiptSettings =
{ {
	{{{"Toggle writing receipt", "\033[34m"}, {"Save receipt to default location", "\033[32m"}, {"Save receipt to program location", "\033[33m"}, {}}},
	{{{"Save receipt to custom location", "\033[31m"}, {"Back", "\033[35m"}, {"Back to Home", "\033[36m"}, {}}},
	{{{}, {}, {}, {}}},
} };