#ifndef CLASENFA_H
#define CLASENFA_H
#include <iostream>
#include "ClaseEstado.h"
#include "SimbolosEspeciales.h"
#include <vector>
#include <stack>

/**
 * @class NFA
 * @brief Represents a Non-Deterministic Finite Automaton (NFA).
 *
 * This class provides operations to build, combine and manipulate
 * NFAs, including union, concatenation, positive closure,
 * Kleene closure, and epsilon transitions.
 *
 * The NFA class is designed around Thompson's construction algorithm.
 *
 * @note NFA stands for Non-deterministic Finite Automaton or in spanish
 * NFA - Automata Finito No Determinista.
 */
class NFA{
    // TODO: Check these attributes if they should be private
    public: //private:
        int counter;
        int EdoIni;
        std::vector<Estado> EdoNFA;
        std::vector<Estado> EdoAcept;
        std::vector<char> Alfabeto;
        bool SeAgregoNFAUnionLexico; //sin informacion por el momento
        int IdNFA;

    public:
        // @brief Constructs an empty NFA
        NFA();

        /**
         * @brief Creates a basic NFA for a single symbol
         * @param symbol The symbol for the transition
         * @param initialCounter The starting state counter
         * @return A basic NFA for the given symbol
         */
        NFA createBasic (char symbol,int initialCounter);

        /**
         * @brief Creates a basic NFA for a range of characters
         * @param firstSymbol The starting character of the range for the transition
         * @param lastSymbol The ending character of the range for the transition
         * @param initialCounter The starting state counter
         * @return A basic NFA for the given character range
         */
        NFA createBasic (char firstSymbol,char lastSymbol,int initialCounter);

        /**
         * @brief Makes a union of two NFAs
         * @param automaton The NFA to concatenate with
         * @return The concatenated NFA
         */
        NFA makeUnion (NFA automataton);

        /**
         * @brief Makes a Concatenation of two NFAs
         * @param automaton The NFA to concatenate with
         * @return The concatenated NFA
         */
        NFA makeConcat (NFA automaton);

        /**
         * @brief Applies positive closure of an NFA
         * @return The NFA after applying positive closure
         */
        NFA applyPositiveClosure();

        /**
         * @brief Kleene closure of an NFA
         * @return The NFA after applying Kleene closure
         */
        NFA applyKleeneClosure();

        /**
         * @brief Makes a Epsilon optional operation on an NFA
         * @return The NFA after applying the optional operation
         */
        NFA makeOptional();

        /**
         * @brief Computes the epsilon closure for a given state
         * @param state initial state from which to compute the epsilon closure
         * @return The set of states reachable from the given state via epsilon transitions
         */
        std::vector<Estado> computeEpsilonClosure (Estado state);

        /**
         * @brief Computes the epsilon closure for a set of states
         * @param states Set of states from which to compute the epsilon closure
         * @return The set of states reachable from the given states via epsilon transitions
         */
        std::vector<Estado> computeEpsilonClosure(std::vector<Estado> states);

        /**
         * @brief Computes the set of states reachable from a set of states via a given symbol
         * @param states Set of states from which to move
         * @param symbol The symbol used for the transitions
         * @return The set of states reachable from the given states via the specified symbol
         */
        //Regresa el cnjunto de estado a los que me puedo mover con el simbolo
        std::vector<Estado> computeMove(std::vector<Estado> states,char symbol);

        /**
         * @brief Computes the GOTO operation for the given set of states and input symbol.
         *
         * This function returns the epsilon-closure of all states reachable by
         * applying the Move operation on the given states with the specified symbol.
         *
         * Equivalent to: GOTO(S, a) = ε-closure(Move(S, a)).
         *
         * @param states The set of NFA states from which the transition begins.
         * @param symbol The input symbol triggering the transition.
         * @return A vector containing the resulting set of states.
         */
        std::vector<Estado> computeGoto(std::vector<Estado> states,char symbol);

        /**
         * @brief Builds the special-union of this NFA with another NFA.
         *
         * This operation merges the current automaton with the given NFA `automaton`
         * using the "special union" construction. The method creates a new initial state,
         * connects it to the initial states of both NFAs using EPSILON transitions,
         * and assigns the specified token and global counter to the resulting
         * accept states.
         *
         * @param automaton The NFA to be merged with this automaton.
         * @param token The token value associated with the resulting accept states.
         * @param globalCounter A global counter used for state indexing.
         */
        void buildSpecialUnion(NFA automaton, int token, int globalCounter);

        /**
         * @brief Returns the value of the last created state counter
         */
        int getCounter();

        /**
         * @brief Displays the NFA's adjacency matrix
         * @param automaton The NFA whose adjacency matrix is to be displayed
         */
        void showAdjacencyMatrix(NFA automaton);

        /**
         * @brief Destructor for the NFA class
         */
        virtual ~NFA();
};

#endif // CLASENFA_H
