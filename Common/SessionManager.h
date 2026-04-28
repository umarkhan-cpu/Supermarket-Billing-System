#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "User.h"
#include <ctime>

class SessionManager {
private:
    // ----- Static state (defined in .cpp) -----
    static User* currentUser;      // non-owning pointer; nullptr if no session
    static time_t loginTime;       // when the session started
    static time_t lastActivity;    // last time updateActivity was called
    static int    timeoutLimit;    // seconds; 600 = 10 minutes (fixed)

public:
    // ----- Session lifecycle -----

    // Start a new session for the given user. Resets all timers.
    // If a session already exists, ends it first (replacement semantics).
    // Returns false if u is nullptr.
    static bool startSession(User* u);

    // End the current session. Clears all state. Safe to call when
    // no session exists (no-op).
    static void endSession();

    // ----- Activity tracking -----

    // Call this whenever the user does something meaningful (button click,
    // menu choice, etc.). Resets the inactivity timer.
    // Safe no-op if no session exists.
    static void updateActivity();

    // Returns true if the session has been inactive for more than
    // timeoutLimit seconds. Returns false if no session exists.
    // Pure query - does NOT end the session itself.
    static bool checkTimeout();

    // ----- Queries -----

    // Returns the currently logged-in user, or nullptr if no session.
    static User* getCurrentUser();

    // How many seconds since the session started.
    // Returns 0 if no session exists.
    static int getSessionDuration();

    // How many seconds remain before timeout fires.
    // Returns 0 if no session exists or already timed out.
    static int getSecondsRemaining();

    // ----- Role queries -----

    // Returns true if a session exists AND the current user is an Admin.
    // Returns false if no session or user is a Cashier.
    static bool isAdmin();

    // Returns true if a session exists AND the current user is a Cashier.
    // Returns false if no session or user is an Admin.
    static bool isCashier();
};

#endif
