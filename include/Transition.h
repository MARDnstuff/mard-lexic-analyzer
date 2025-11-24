#ifndef TRANSITION_H
#define TRANSITION_H


/**
 * @class Transition
 * @brief Represents a transition between states in an automaton.
 * 
 * This class encapsulates the details of a transition, including
 * the input symbols that trigger the transition, as well as the
 * source and destination states.
 */
class Transition {
    private:
        // @brief Lower symbol for the transition
        char lowerSymbol;
        // @brief Upper symbol for the transition
        char upperSymbol;
        // @brief Identifier of the destination state
        int targetStateId;
        // @brief Identifier of the source state
        int sourceStateId;

    public:

        /**
         * @brief Constructor for a single symbol transition
         * @param symbol The symbol that triggers the transition
         * @param sourceId The identifier of the source state
         * @param targetId The identifier of the destination state
         * @return A transition object for the specified symbol and states
         */
        Transition(char symbol, int sourceId, int targetId):
            lowerSymbol(symbol), upperSymbol(symbol),
            sourceStateId(sourceId), targetStateId(targetId) {}

        /**
         * @brief Constructor for a range of symbols transition
         * @param lowSymbol The lower bound symbol of the range
         * @param upSymbol The upper bound symbol of the range
         * @param sourceId The identifier of the source state
         * @param targetId The identifier of the destination state
         * @return A transition object for the specified symbol range and states
         */
        Transition (char lowSymbol, char upSymbol, int sourceId ,int targetId): 
            lowerSymbol(lowSymbol), upperSymbol(upSymbol),
            sourceStateId(sourceId), targetStateId(targetId) {}

        /**
         * @brief Sets a transition for a single symbol
         * @param symbol The symbol that triggers the transition
         * @param sourceId The identifier of the source state
         * @param targetId The identifier of the destination state 
         * @return void
         */
        void setTransition(char symbol, int sourceId, int targetId);

        /**
         * @brief Sets a transition for a range of symbols
         * @param lowSymbol The lower bound symbol of the range
         * @param upSymbol The upper bound symbol of the range
         * @param sourceId The identifier of the source state
         * @param targetId The identifier of the destination state
         */
        void setTransition(char lowerSymbol, char upperSymbol, int sourceId, int targetId);

        /**
         * @brief Returns lower symbol of the transition 
         */
        char getLowerSymbol();

        /**
         * @brief Sets lower symbol of the transition
         * @param symbol The lower symbol to set
         * @return void
         */
        void setLowerSymbol (char symbol);

        /**
         * @brief Returns upper symbol of the transition
         * @return The upper symbol of the transition
         */
        char getUpperSymbol ();

        /**
         * @brief Sets upper symbol of the transition
         * @param symbol The upper symbol to set
         * @return void
         */
        void setUpperSymbol(char symbol);

        /**
         * @brief Return the identifier of the destination state
         * @param symbol The symbol triggering the transition
         * @return The identifier of the destination state
         */
        int getTransitionState (char symbol);

        /**
         * @brief Sets the sources state identifier
         * @param sourceId The identifier of the source state
         * @return void
         */
        // Establece el estado origen
        void setSourceStateId (int sourceId);

        /**
         * @brief Returns the source state identifier
         * @return The identifier of the source state
         */
        // Regresa el estado origen
        int getSourceStateId ();

        /**
         * @brief Sets the destination state identifier
         * @param targetId The identifier of the destination state
         * @return void
         */
        void setTargetStateId(int targetId);

        /**
         * @brief Returns the destination state identifier
         * @return The identifier of the destination state
         */
        int getTargetStateId ();

        /**
         * @brief Destructor for the Transition class
         */
        virtual ~Transition();
};

#endif // TRANSITION_H
