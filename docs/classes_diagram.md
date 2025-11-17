# Project class diagram

This file contains a Mermaid class diagram representing the relationships between the main classes in this repository (inferred from headers under `include/`).

Generated: 2025-11-17

## Mermaid diagram

```mermaid
classDiagram
    %% Core automata classes
    class AFD {
        +vector<int> flag
        +vector<char> Alfabeto
        +int **Mx_adyacencia
        +Conv_NFAaAFD(NFA)
    }
    class NFA {
        +int Contador
        +vector<Estado> EdoNFA
        +NFA_Basico(...)
    }
    class ConIj {
        +vector<Transicion> Trans1
        +vector<Estado> Edos
        +int Token
    }
    class Estado {
        +vector<Transicion> Trans1
        +int idEstado1
    }
    class Transicion {
        +char SimbInf1
        +char SimbSup1
    }

    %% Lexical & evaluation
    class AnalizLexico {
        +string Lexema
        +AFD AutomataFD
        +yylex()
    }
    class Estado_AnalizLexico {
        +int token
        +string Lexema
        +stack<int> Pila
    }
    class ER_NFA {
        +NFA result
        +AnalizLexico L
    }
    class EvaluadorExp1 {
        +string Expresion
        +AnalizLexico L
    }

    %% Grammar / parser classes
    class ClaseNodo {
        +string Simbolo
        +bool Terminal
    }
    class ElemArreglo {
        +ClaseNodo InfSimbolo
        +vector<ClaseNodo> ListaLadoDerecho
    }
    class DescRecGram_Gram {
        +string Gramatica
        +AnalizLexico L
        +ElemArreglo ArrReglas[100]
        +vector<ClaseNodo> Vn
        +vector<ClaseNodo> Vt
    }
    class AnalizadorLL1 {
        +DescRecGram_Gram DescRecG
        +AnalizLexico LexGram
        +SimbTerm *Vt
    }
    class Simb {
        +string cadena
        +bool Terminal
    }
    class SimbTerm {
        +string Simbolo
        +int ValToken
    }

    %% Relationships (composition / aggregation / association)
    AFD *-- ConIj : has
    AFD --> NFA : uses (conversion)
    ConIj *-- Transicion : has
    ConIj *-- Estado : has
    Estado *-- Transicion : has
    NFA *-- Estado : has
    ER_NFA *-- NFA : result
    ER_NFA *-- AnalizLexico : uses
    AnalizLexico *-- AFD : owns/uses automaton
    AnalizLexico --> Estado_AnalizLexico : returns/accepts (API)
    DescRecGram_Gram *-- AnalizLexico : uses/internal lexer
    DescRecGram_Gram *-- ElemArreglo : contains rules
    DescRecGram_Gram *-- ClaseNodo : contains Vn/Vt
    ElemArreglo *-- ClaseNodo : has
    AnalizadorLL1 *-- DescRecGram_Gram : contains
    AnalizadorLL1 *-- AnalizLexico : contains/uses
    AnalizadorLL1 o-- SimbTerm : Vt pointer (aggregation)
    AnalizadorLL1 o-- Simb : uses
    EvaluadorExp1 *-- AnalizLexico : has
    EvaluadorExp1 --> AFD : uses (constructor param)
```

## Notes and assumptions

- Composition (`*--`) indicates ownership because headers show member variables of the other class (e.g., `AFD` has `std::vector<ConIj>`).
- Association/usage (`-->` or `o--`) indicates looser coupling (method parameters, return types, or pointers).
- No inheritance (`class X : public Y`) was found in the headers scanned, so the diagram shows composition and associations only.
- The diagram was built from the public headers under `include/`. There may be additional private/internal relationships in `src/` implementations; say the word and I will scan `src/` to enrich the diagram.

## How to view

- If your editor supports Mermaid (e.g., VS Code with a Mermaid preview extension), open this file and use the preview.
- Use an online Mermaid live editor or tools like `mmdc` to render to SVG/PNG.
