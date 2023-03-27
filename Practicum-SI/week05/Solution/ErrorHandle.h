#pragma once

// Enum for error handling
enum class State {
    OK,
    NegativeBalance,
    NegativeQuantity,
    NegativePrice,
    UserFull,
    ProductFull,
    PriceFull,
    UserNotFound,
    ProductNotFound,
    ShortOnMoney,
    NotEnoughItems
};