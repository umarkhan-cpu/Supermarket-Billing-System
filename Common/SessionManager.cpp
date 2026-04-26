#include "SessionManager.h"

// ============================================================================
// Static member definitions
// ============================================================================

User* SessionManager::currentUser = nullptr;
time_t SessionManager::loginTime = 0;
time_t SessionManager::lastActivity = 0;
int    SessionManager::timeoutLimit = 600;   // 10 minutes in seconds

// ============================================================================
// Session lifecycle
// ============================================================================

bool SessionManager::startSession(User* u)
{
    if (!u) return false; // No user/session

    endSession(); // Stop already existing session

    currentUser = u;
    loginTime = time(nullptr);  // Capture current time
    lastActivity = loginTime;   // Login counts as the first activity
    
    return true; // session started successfully
}

// Clear all state. Safe to call even if no session exists.
void SessionManager::endSession()
{
    currentUser = nullptr;
    loginTime = 0;
    lastActivity = 0;
}

// ============================================================================
// Activity tracking
// ============================================================================

void SessionManager::updateActivity()
{
    if (!currentUser) return;

    lastActivity = time(nullptr); // Update last activity to now
}

bool SessionManager::checkTimeout()
{
    if (!currentUser) return false;

    time_t now = time(nullptr);                   // Current time
    double elapsed = difftime(now, lastActivity); // Time passed since last activity - returns seconds(double)

    if (elapsed > timeoutLimit) // If elapsed time is greater than 10 mins, send signal to logout
        return true;
    else
        return false;
}

// ============================================================================
// Queries
// ============================================================================

User* SessionManager::getCurrentUser()
{
    return currentUser;
}

int SessionManager::getSessionDuration()
{
    if (!currentUser) 
        return 0;
    else
        return (int)difftime(time(nullptr), loginTime); // Returns the duration of a session if exists
}

int SessionManager::getSecondsRemaining()
{
    if (!currentUser) return 0;

    time_t now = time(nullptr);
    double elapsed = difftime(now, lastActivity);  // Calculate elapsed time
    int remaining = timeoutLimit - (int)elapsed;   // Calculate remaining time

    if (remaining < 0)
        return 0; // session already timed out
    else
        return remaining;
}

// ============================================================================
// Role queries
// ============================================================================

bool SessionManager::isAdmin()
{
    if (!currentUser) return false;
    return currentUser->getRoleName() == "Admin";
}

bool SessionManager::isCashier()
{
    if (!currentUser) return false;
    return currentUser->getRoleName() == "Cashier";
}