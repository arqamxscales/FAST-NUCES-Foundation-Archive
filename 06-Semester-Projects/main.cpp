//
//  main.cpp
//  PSX-Alpha Simulator
//
//  Created by Arqam´s on 1/21/26.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

// --- PSX-Alpha: HFT Core Logic Simulation ---
// Author: Mohammad Arqam Javed
// Purpose: Simulate a Limit Order Book with Price-Time Priority matching.

// Enum to identify the side of the trade
enum class Side {
    BUY,
    SELL
};

// Represents a single order in the market
struct Order {
    int id;
    double price;
    int quantity;
    Side side;
    long timestamp; // Used for Time-Priority (FIFO)

    // Constructor
    Order(int _id, double _price, int _qty, Side _side)
        : id(_id), price(_price), quantity(_qty), side(_side) {
        timestamp = std::time(nullptr); // Capture current time
    }
};

// The Engine
class OrderBook {
private:
    // We use std::map because it keeps keys (prices) sorted automatically.
    // Bids (Buys): We want the HIGHEST price at the top (std::greater).
    std::map<double, std::vector<Order>, std::greater<double>> bids;

    // Asks (Sells): We want the LOWEST price at the top (std::less - default).
    std::map<double, std::vector<Order>> asks;

public:
    // Adding an order triggers the matching engine immediately
    void add_order(int id, double price, int quantity, Side side) {
        // Logging the incoming request
        std::cout << "[REQ] New Order: " << (side == Side::BUY ? "BUY " : "SELL ")
                  << quantity << " @ " << price << std::endl;

        // Try to match the order before adding it to the book
        int remaining_qty = match_order(id, price, quantity, side);

        // If there is quantity left after matching, add it to the book
        if (remaining_qty > 0) {
            Order new_order(id, price, remaining_qty, side);
            if (side == Side::BUY) {
                bids[price].push_back(new_order);
            } else {
                asks[price].push_back(new_order);
            }
        }
    }

    // The "Matching Engine"
    int match_order(int id, double price, int quantity, Side side) {
        int remaining_qty = quantity;

        if (side == Side::BUY) {
            // Buying? Look at the ASKS (Sells)
            // While we have quantity to fill AND there are sellers available
            while (remaining_qty > 0 && !asks.empty()) {
                auto best_ask_iter = asks.begin(); // Lowest sell price
                double best_price = best_ask_iter->first;
                std::vector<Order>& order_queue = best_ask_iter->second;

                // Logic: If I want to buy at 100, and someone sells at 101, NO DEAL.
                if (price < best_price) break;

                // Process orders at this price level (FIFO - First In, First Out)
                while (remaining_qty > 0 && !order_queue.empty()) {
                    Order& sell_order = order_queue.front();
                    
                    int trade_qty = std::min(remaining_qty, sell_order.quantity);
                    
                    // EXECUTE
                    std::cout << ">>> [TRADE] Matched " << trade_qty << " units @ "
                              << best_price << " (Buyer: " << id << ", Seller: " << sell_order.id << ")" << std::endl;

                    remaining_qty -= trade_qty;
                    sell_order.quantity -= trade_qty;

                    // If seller is out of stock, remove their order
                    if (sell_order.quantity == 0) {
                        order_queue.erase(order_queue.begin());
                    }
                }

                // If no more sellers at this price, remove the price level
                if (order_queue.empty()) {
                    asks.erase(best_ask_iter);
                }
            }
        }
        else { // Side == SELL
            // Selling? Look at the BIDS (Buys)
            while (remaining_qty > 0 && !bids.empty()) {
                auto best_bid_iter = bids.begin(); // Highest buy price
                double best_price = best_bid_iter->first;
                std::vector<Order>& order_queue = best_bid_iter->second;

                // Logic: If I want to sell at 100, but best buyer is at 99, NO DEAL.
                if (price > best_price) break;

                while (remaining_qty > 0 && !order_queue.empty()) {
                    Order& buy_order = order_queue.front();

                    int trade_qty = std::min(remaining_qty, buy_order.quantity);

                    // EXECUTE TRADE
                    std::cout << ">>> [TRADE] Matched " << trade_qty << " units @ "
                              << best_price << " (Seller: " << id << ", Buyer: " << buy_order.id << ")" << std::endl;

                    remaining_qty -= trade_qty;
                    buy_order.quantity -= trade_qty;

                    if (buy_order.quantity == 0) {
                        order_queue.erase(order_queue.begin());
                    }
                }

                if (order_queue.empty()) {
                    bids.erase(best_bid_iter);
                }
            }
        }
        return remaining_qty;
    }

    void print_book() {
        std::cout << "\n--- CURRENT ORDER BOOK ---" << std::endl;
        std::cout << "ASKS (Sells):" << std::endl;
        // Iterate backwards (rbegin) to show highest price sells at top?
        // Actually, standard is usually lowest sell closest to spread.
        for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
            std::cout << "  Price: " << it->first << " | Vol: ";
            int total = 0;
            for(const auto& o : it->second) total += o.quantity;
            std::cout << total << std::endl;
        }

        std::cout << "--------------------------" << std::endl;

        std::cout << "BIDS (Buys):" << std::endl;
        for (const auto& pair : bids) {
            std::cout << "  Price: " << pair.first << " | Vol: ";
            int total = 0;
            for(const auto& o : pair.second) total += o.quantity;
            std::cout << total << std::endl;
        }
        std::cout << "--------------------------\n" << std::endl;
    }
};

//  SIMULATION
int main() {
    OrderBook psx_engine;

    std::cout << "Initializing PSX-Alpha Simulation...\n" << std::endl;

    // 1. Setup liquidity (Passive Makers)
    // Someone wants to sell OGDC at 105.50
    psx_engine.add_order(101, 105.50, 100, Side::SELL);
    // Someone wants to sell OGDC at 106.00
    psx_engine.add_order(102, 106.00, 50, Side::SELL);
    
    // Someone wants to buy at 104.00
    psx_engine.add_order(201, 104.00, 200, Side::BUY);

    psx_engine.print_book();

    // 2. Incoming Market Order
    // AI predicts price UP, decides to Buy 120 shares aggressively at 105.50
    // Logic: Matches 100 shares at 105.50, remaining 20 sit in book
    psx_engine.add_order(301, 105.50, 120, Side::BUY);

    psx_engine.print_book();

    return 0;
}
