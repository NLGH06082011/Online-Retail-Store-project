using namespace std;
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <fcntl.h>
#include <rpc.h>
#include <shobjidl.h>
#include <windows.h>
#include <shellapi.h>
#include <conio.h>
#include <io.h>
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "Rpcrt4.lib")
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <limits>
#include <optional>
#include <iomanip>
#include <stdexcept>
#include <array>
#include <sstream>
#include "product.h"
#include "inventory.h"
#include <string>
#include "search.h"
#include "createProducts.cpp"
#include <random>
#include <fstream>
#include "ui_underlie.h"
#include "ui_buttonList.h"
#include "ui_main.h"