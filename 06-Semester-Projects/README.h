//
//  README.h
//  PSX-Alpha Simulator
//
//  Created by Arqam´s on 1/21/26.
//

#`README.md`
PSX-Alpha 🚀
**A High-Frequency Trading (HFT) Simulator for the Pakistan Stock Exchange**


PSX-Alpha is a low-latency trading engine designed to simulate the microstructure of the Pakistan Stock Exchange (PSX). Built in C++, it implements a high-performance Limit Order Book (LOB) with a focus on Price-Time Priority and memory efficiency.

🎯 Project Overview

The goal of this project is to model how institutional-grade HFT systems operate in the local market. By combining low-level systems engineering with AI-driven strategy, PSX-Alpha demonstrates how nanosecond-level logic can be used to navigate the KSE-100 index.

Key Features
Core Matching Engine: Implements a full Limit Order Book with FIFO (First-In-First-Out) execution logic.
Performance Optimized: Uses sorted maps and efficient vector management to minimize "Tick-to-Trade" latency.
PSX Microstructure: Specifically tuned to handle PSX-specific price increments (ticks) and order types.
AI Strategy Layer: (In Progress) A lightweight Decision Tree model that predicts short-term price movements based on Order Book Imbalance.


🛠 Tech Stack
Language: C++
Data Structures: Custom Limit Order Book (LOB) using `std::map` and `std::vector`.
Methodology: Object-Oriented Programming (OOP) & Data-Oriented Design.

Build the project:
```bash
mkdir build && cd build
cmake ..
make

Execute the simulator:
```bash
./psx_engine


📊 System Architecture

The engine follows a modular pipeline to ensure zero-bottleneck processing:

1. Ingestion: Receives market updates (Bids/Asks).
2. Matching: Compares the new order against the existing LOB.
3. Execution: If prices overlap, a trade is generated and logs are updated.
4. Reporting: Real-time visualization of the order book spread.

🤝 Contributing

Contributions are welcome! If you have ideas for low-latency optimizations or PSX-specific strategies, feel free to open an issue or submit a pull request.


**Developed by [Mohammad Arqam Javed**] (https://www.google.com/search?q=https://www.linkedin.com/in/mohammad-arqam-j-516975343/)
