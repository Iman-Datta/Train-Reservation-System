# 🚆 Train Reservation System (C Project)

## 📌 Overview
This is a **Terminal-based Train Reservation System in C**.  
It simulates ticket booking, cancellation, seat assignment, and waiting list management.  

The project uses:
- **Arrays** → to track booked/unbooked seats  
- **Linked List** → to store passenger details (Name, Age, Seat Number)  
- **Queue (FIFO)** → to manage the waiting list when all seats are booked  

---

## 🎯 Features
1. **Book Ticket**
   - Assigns the first available seat.
   - If all seats are full → passenger goes into the **waiting list**.
   - If waiting list is also full → booking is denied.

2. **Cancel Ticket**
   - Frees up the seat.
   - If waiting list has passengers → the **first waiting passenger automatically gets the seat**.

3. **View Reservations**
   - Shows all confirmed passengers and their seat numbers.

4. **View Waiting List**
   - Shows all passengers currently waiting for a seat.

5. **Exit**
   - Closes the program.

---

## 🖥️ User Experience
- ✅ Book ticket if seats are free.  
- ⚠️ Go into waiting list if train is full.  
- 🎟️ If someone cancels, first passenger in waiting list gets the seat automatically.  
- ❌ If waiting list is also full, booking request is denied.  

---

## ⚙️ How to Compile & Run
1. Save the code into a file named `train_reservation.c`.
2. Open terminal/command prompt in that directory.
3. Compile using:
   ```bash
   gcc train_reservation.c -o train_reservation
