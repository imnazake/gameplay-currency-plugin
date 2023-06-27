// Copyright Neoxyne. All Rights Reserved.

#include "CurrencyData.h"

const FCurrencyData FCurrencyData::ZeroCurrency = FCurrencyData();

FCurrencyData::FCurrencyData()
{
	CopperCoins = 0;
	SilverCoins = 0;
	GoldCoins = 0;
}