#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 5
#define MAX_NAME 50
#define WAITING_CAPACITY 5

// Passenger linked list node
typedef struct Passenger {
    char name[MAX_NAME];
    int age;
    int seatNo;
    struct Passenger* next;
} Passenger;

// Queue for waiting list
typedef struct {
    char name[WAITING_CAPACITY][MAX_NAME];
    int age[WAITING_CAPACITY];
    int front, rear, size;
} Queue;

// Globals
Passenger* head = NULL;
int seats[MAX_SEATS] = {0}; // 0 = empty, 1 = booked
Queue waitingList = {.front = 0, .rear = -1, .size = 0};

// Queue functions
int isFull(Queue* q) { return q->size == WAITING_CAPACITY; }
int isEmpty(Queue* q) { return q->size == 0; }

void enqueue(Queue* q, char* name, int age) {
    if (isFull(q)) {
        printf("\nWaiting list is FULL! Cannot add more.\n");
        return;
    }
    q->rear = (q->rear + 1) % WAITING_CAPACITY;
    strcpy(q->name[q->rear], name);
    q->age[q->rear] = age;
    q->size++;
}

void dequeue(Queue* q, char* name, int* age) {
    if (isEmpty(q)) return;
    strcpy(name, q->name[q->front]);
    *age = q->age[q->front];
    q->front = (q->front + 1) % WAITING_CAPACITY;
    q->size--;
}

// Linked list insert
void addPassenger(char* name, int age, int seatNo) {
    Passenger* newP = (Passenger*)malloc(sizeof(Passenger));
    strcpy(newP->name, name);
    newP->age = age;
    newP->seatNo = seatNo;
    newP->next = head;
    head = newP;
}

// Delete passenger by seat number
void removePassenger(int seatNo) {
    Passenger *temp = head, *prev = NULL;
    while (temp != NULL && temp->seatNo != seatNo) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return; // not found

    if (prev == NULL) head = temp->next;
    else prev->next = temp->next;

    free(temp);
}

// Book ticket
void bookTicket() {
    char name[MAX_NAME];
    int age, seatNo = -1;

    printf("\nEnter Name: ");
    gets(name);
    printf("Enter Age: ");
    scanf("%d", &age);

    // Find empty seat
    for (int i = 0; i < MAX_SEATS; i++) {
        if (seats[i] == 0) {
            seatNo = i + 1;
            seats[i] = 1;
            addPassenger(name, age, seatNo);
            printf("\n✅ Ticket booked! Seat No: %d\n", seatNo);
            return;
        }
    }

    // If no seat → waiting list
    if (!isFull(&waitingList)) {
        enqueue(&waitingList, name, age);
        printf("\nAll seats are full! Added to waiting list.\n");
    } else {
        printf("\nNo seats and waiting list is also full!\n");
    }
}

// Cancel ticket
void cancelTicket() {
    int seatNo;
    printf("\nEnter Seat No to cancel: ");
    scanf("%d", &seatNo);

    if (seatNo < 1 || seatNo > MAX_SEATS || seats[seatNo - 1] == 0) {
        printf("\n Invalid seat number or not booked.\n");
        return;
    }

    seats[seatNo - 1] = 0;
    removePassenger(seatNo);
    printf("\n✅ Ticket for Seat %d cancelled.\n", seatNo);

    // Assign to waiting list passenger if available
    if (!isEmpty(&waitingList)) {
        char wName[MAX_NAME];
        int wAge;
        dequeue(&waitingList, wName, &wAge);
        seats[seatNo - 1] = 1;
        addPassenger(wName, wAge, seatNo);
        printf("🎟️ Seat reassigned to waiting list passenger: %s\n", wName);
    }
}

// Show booked tickets
void viewReservations() {
    Passenger* temp = head;
    if (temp == NULL) {
        printf("\nNo reservations yet.\n");
        return;
    }
    printf("\n--- Reserved Seats ---\n");
    while (temp != NULL) {
        printf("Seat %d -> %s (Age %d)\n", temp->seatNo, temp->name, temp->age);
        temp = temp->next;
    }
}

// Show waiting list
void viewWaitingList() {
    if (isEmpty(&waitingList)) {
        printf("\nWaiting list is empty.\n");
        return;
    }
    printf("\n--- Waiting List ---\n");
    int idx = waitingList.front;
    for (int i = 0; i < waitingList.size; i++) {
        printf("%d. %s (Age %d)\n", i + 1, waitingList.name[idx], waitingList.age[idx]);
        idx = (idx + 1) % WAITING_CAPACITY;
    }
}

// Menu
int main() {
    int choice;
    while (1) {
        printf("\n==== Train Reservation System ====\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. View Reservations\n");
        printf("4. View Waiting List\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: cancelTicket(); break;
            case 3: viewReservations(); break;
            case 4: viewWaitingList(); break;
            case 5: printf("\nGoodbye!\n"); exit(0);
            default: printf("\nInvalid choice. Try again.\n");
        }
    }
    return 0;
}