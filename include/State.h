#ifndef STATE_H
#define STATE_H
#include <vector>
#include "Transition.h"

/**
 * @class State
 * @brief Represents a state in a finite automaton.
 *
 * This class encapsulates the properties and behaviors of a state,
 * including its identifier, acceptance status, associated token,
 * and transitions to other states.
 */
class State {
    public:
        // @brief Counter for unique state identifiers
        // NOTE: This should ideally be static to ensure uniqueness across all instances
        int idStateCounter = 0;
        
        // @brief Set of transitions for the state
        std::vector<Transition> transitions;

    private:
        // @brief State Identifier
        int stateId;

        // @brief Acceptance state flag
        bool acceptanceState;

        // @brief Unique token for acceptance states
        int token;

    public:
        /**
         * @brief Constructor for the State class
         */
        State();

        /**
         *  @brief Gets the state identifier
         *  @return The state identifier
         */
        int getStateId();

        /**
         * @brief Sets the state identifier
         * @param id The identifier to set
         * @return void
         */
        void setStateId(int id);

        /**
         * @brief Tells if the state is an acceptance state
         * @return True if it is an acceptance state, false otherwise
         */
        bool isAcceptanceState();

        /**
         * @brief Sets the acceptance state flag
         * @param value True to set as acceptance state, false otherwise
         * @return void
         */
        void setAcceptanceState(bool value);

        /**
         * @brief Gets the unique token for the acceptance state
         * @return The token value
         */
        int getToken();

        /**
         * @brief Sets the unique token for the acceptance state
         * @param value The token value to set
         * @return void
         */
        void setToken(int value);

        /**
         *  @brief Returns the set of transitions associated with the state
         *  @return The vector of transitions
         */
        std::vector<Transition>  getTransitions (){
            return transitions;
        }

        /**
         * @brief Adds a transition to the state's transition set
         * @param value The transition to add
         * @return The updated vector of transitions
         */
        void addTransition (Transition newTransition);

        /**
         * @brief Destructor for the State class
         */
        virtual ~State();

};

#endif // STATE_H
