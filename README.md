# Matrix calculator (téma: Maticová kalkulačka)
Autor: Troják Jan - trojaj12 _<trojaj12@fit.cvut.cz>_
## Zadání z progtestu
Vytvořte aplikaci implementující maticovou kalkulačku.

Kalkulačka musí implementovat:

    - práci s maticemi různé velikosti
    - základní operace: sčítání, odčítání, násobení, transpozice
    - sloučení (3x3 sloučeno s 3x3 => matice 6x3) a oříznutí (např. pouze levá polovina matice 6x3 => levá 3x3)
    - pro čtvertcové matice navíc výpočet inverze
    - efektivní paměťovou reprezentaci (pro řídké matice se nehodí 2D pole, pro husté matice naopak)
    - funkce pro výpočet determinantu, určení hodnosti, Gaussova eliminační metoda
    - proměnné (uložení matice do proměnné, načítání matice ze vstupu, využití proměnné ve výpočtu)

## Vlastní upravené zadání
Vytvořte aplikaci implementující maticovou kalkulačku.

Kalkulačka bude zvládat:

    - základní matematické operace (sčítání, odčítání, násobení)
    - základní práce s maticemi (transpozice, spojení dvou matic, oříznout matice)
    - výpočet hodnosti, determinantu a inverzní matice (pokud možno)
    - převádět matice do horního stupňovitého tvaru (HST)
    - implementace GEMu s komentářem a bez
    - ukládat matice do proměnných
    - načítat/ukládat paměť kalkulačky z/do souborů

## Rozvaha implementace
Aplikace bude rozdělena do 3 hlavních částí. Konkrétně do částí:

### UI
Tato část bude implementovat uživatelské rozhraní. Tato část bude obsahovat celkem 2 třídy.

 - Třída **CUserInterface** bude zpostředkovávat komunikaci s uživatelem. Bude zpracovávat vstupy a výstupy.
 - Třída **UIText** bude statická třída, která bude uchovávat texty, které bude *CUserInterface* používat.


### Calculator
Tato část bude implementovat samotnou kalkulačku. Třída bude obsahovat pouze jednu třídu.

 - Třída **CCalculator** bude ukládat samotné matice a pracovat s nimi. Dále bude umožňovat uložit/načíst svou paměť ze/do souboru.

### Matrix
Poslední část se bude starat o reprezentaci samotných matic a vnitřní počítaní s nimi. Tato část bude obsahovat celkem 4 třídy.

 - Abstraktní třída **CMatrix** tato třída se bude navenek chovat jako třída pracující s maticemi.
 - Abstraktní třída **CSparseMatrix** tato třída bude potomkem třídy *CMatrix* a bude reprezentovat tzv. řidké matice.
   Řidké matice jsou matice, které z velké části obsahují nuly. U těchto matic je zbytečné uchovávat tyto opakující se nuly, proto budou ukládány pouze pozice, které nuly nejsou.
 - Abstraktní třída **CDenseMatrix** tato třída bude potomkem třídy *CMatrix* a bude reprezentovat matice, které nebudou reprezentovány jako *CSparseMatrix*.
 - Třída **CLinear** tato třída bude implementovat složitější operace s maticemi, konkrétně Gem, výpočet determinantu, hodnosti a inverzní matice.
 ll

## Použití polymorfismu
Polymorfismus bude použit při vývoji *CMatrix*, konkrétně se bude využívat pro implementaci funkcí: (informace o jednotlivých
funkcí můžete najít v hlavičkovém souboru)

    - T                             CMatrix::operator ()        ( unsigned row , unsigned col )
    - std::shared_ptr < CMatrix >   CMatrix::mergeHorizontally  ( const CMatrix & )
    - std::shared_ptr < CMatrix >   CMatrix::mergeVertically    ( const CMatrix & )
    - std::shared_ptr < CMatrix >   CMatrix::Clone              ( )
    - std::shared_ptr < CMatrix >   CMatrix::Transpose          ( )
    - void                          CMatrix::CountNumberOfNulls ( )
    - std::shared_ptr < CMatrix >   CMatrix::CreateNew          ( std::deque < T > & )
---
