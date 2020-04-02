#include <vector>
#include <stdexcept>

#include "reversi.h"

using namespace std;


Square& Square::operator=(SquareValue value){
    this-> value_ = value;
    return *this;
}

bool Square::operator==(SquareValue value) const
{
    return (this-> value_ == value);
}

bool Square::operator!=(SquareValue value) const
{
    return (this-> value_ != value);
}

void Square::flip()
{
    switch (value_)
    {
    case WHITE:
        value_ = BLACK;
        break;
    case BLACK:
        value_ = WHITE;
        break;
    default:
        break;
    }
}

ostream& operator<<(ostream& out, const Square& square)
{
    if(square.value_ == 0)
        out << "-";
    else if(square.value_ == 1)
        out << "W";
    else if(square.value_ == 2)
        out << "B";

    return out;
}


Square::SquareValue opposite_color(Square::SquareValue value)
{
    switch (value)
    {
    case Square::WHITE:
        return Square::BLACK;
    case Square::BLACK:
        return Square::WHITE;
    default:
        throw invalid_argument("Illegal square value");
    }
}

bool Square::operator==(const Square::SquareValue t)
{
    if(value_ == t)
        return true;
    else
        return false;

}



Board::Board(size_t s)
{
    dimension_ = s;
    squares_ =  new Square * [s];
    for(int i = 0; i < s; i++){
        squares_[i] = new Square[s];
    }
}

Board::Board(const Board &rhs)
{
    dimension_ = rhs.dimension_;
    squares_ = new Square * [rhs.dimension_];
    for(int i = 0; i < dimension_; i++){
        squares_[i] = new Square[dimension_];
    }

    for(int x = 0; x < dimension_; x++){
        for(int y = 0; y < dimension_; y++){
            squares_[x][y] = rhs.squares_[x][y];
        }
    }
}

Board::~Board()
{
    for(int i = 0; i < dimension_; i++){
        delete [] squares_[i];
    }

    delete [] squares_;
}




Square& Board::operator()(char row, size_t column)
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

Square const& Board::operator()(char row, size_t column) const
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

bool Board::is_legal_and_opposite_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] != Square::FREE && squares_[row_index][column - 1] != turn;
    }
    return false;
}

bool Board::is_legal_and_same_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] == turn;
    }
    return false;
}

bool Board::is_valid_location(char row, size_t column) const
{
    size_t row_index = row_to_index(row);
    return row_index < dimension_ && column - 1 < dimension_;
}

Checkpoint::Checkpoint(const Board& b, Square::SquareValue turn) :
    board_(b),
    turn_(turn)
{

}

ostream& Board::print(ostream& out) const
{
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        if (i < 10)
        {
            out << " ";
        }
        else
        {
            out << (i / 10);
        }
    }
    out << endl;
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        out << (i % 10);
    }
    out << endl;
    for (size_t i = 0; i < dimension_; i++)
    {
        out << (char)('a' + i) << ':';
        for (size_t k = 0; k < dimension_; k++)
        {
            out << squares_[i][k];
        }
        out << endl;
    }
    return out;
}

ostream& operator<<(ostream& out, const Board& board)
{
    return board.print(out);
    
}

Board& Board::operator=(const Board &rhs)
{

    this->dimension_ = rhs.dimension();

    for(int x = 0; x < this->dimension_; x++){
        for(int y = 0; y < this->dimension_; y++){
            this->squares_[x][y] = rhs.squares_[x][y];
        }
    }

    return *this;
}


Reversi::Reversi(size_t s) :
    board_(s), turn_(Square::BLACK)
{
    size_t mid = s/2;

    board_(index_to_row(mid), mid) = Square::BLACK;
    board_(index_to_row(mid+1), mid+1) = Square::BLACK;
    board_(index_to_row(mid), mid +1) = Square::WHITE;
    board_(index_to_row(mid+1), mid) = Square::WHITE;

} 

void Reversi::play()
{
    char input;
    char rowPosition;
    size_t colPosition;
    bool gameOver = false;


    while(!is_game_over()){

        prompt();

        cin >> input;
        if(input == 'p'){
            cin >> rowPosition;
            cin >> colPosition;
        
            if(board_(rowPosition, colPosition) == Square::FREE){
                if(is_legal_choice(rowPosition, colPosition, turn_)){
                    board_(rowPosition, colPosition) = turn_;

                }
                else
                    continue;
            
            }
            else{
                continue;
            }

        }

        else if(input == 'c'){
            save_checkpoint();
            continue;
        }
        else if(input == 'u'){
            undo();
            continue;
        }

        else{
            gameOver = true;
            break;
        }

        flipInsides(rowPosition, colPosition, turn_);

        flipColor();
    }


    count();

    if(gameOver || is_game_over()){
        win_loss_tie_message(wcnt, bcnt);


    }
}

void Reversi::count()
{
    for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++)
    {
        for (size_t column = 1; column <= board_.dimension(); column++)
        {
            if (board_(row, column).value_ == Square::BLACK)
            {
                bcnt++;
            }
            else if(board_(row, column).value_ == Square::WHITE)
            {
                wcnt++;
            }
        }
    }
}


void Reversi::flipColor()
{
    if(turn_ == Square::BLACK)
        turn_ = Square::WHITE;
    else if(turn_ == Square::WHITE)
        turn_ = Square::BLACK;

}

void Reversi::flipInsides(char row, size_t column, Square::SquareValue turn)
{
    const size_t direction_count = 8;
    const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
    const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};

    for (size_t d = 0; d < direction_count; d++)
    {
        char cursor_row = row + direction_row[d];
        size_t cursor_column = column + direction_column[d];

        // Move towards the direction while we're on the opposite color
        while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
        {
            cursor_row += direction_row[d];
            cursor_column += direction_column[d];
        }

        // Check if the next thing after is our color
        bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);

        if(found_same){
            char cursor_row = row + direction_row[d];
            size_t cursor_column = column + direction_column[d];

            while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
            {

            board_(cursor_row, cursor_column) = turn;

            cursor_row += direction_row[d];
            cursor_column += direction_column[d];
            }
        }
    }



}



void Reversi::prompt() const
{
    cout << board_ << endl;
    cout << (turn_ == Square::BLACK ? "B" : "W");
    cout << " - Enter 'p r/c', 'q', 'c', 'u':" << endl;
}

void Reversi::win_loss_tie_message(size_t white_count, size_t black_count)
{
    cout << board_ << endl;
    if (white_count > black_count)
    {
        cout << "W wins" << endl;
    }
    else if (white_count < black_count)
    {
        cout << "B wins" << endl;
    }
    else
    {
        cout << "Tie" << endl;
    }
    cout << "W=" << white_count << "/B=" << black_count << endl;
}

bool Reversi::is_legal_choice(char row, size_t column, Square::SquareValue turn) const
{
    // Vectors for each cardinal direction
    const size_t direction_count = 8;
    const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
    const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};

    // Make sure location is free
    if (board_(row, column) != Square::FREE)
    {
        return false;
    }

    // Now check in each directions
    for (size_t d = 0; d < direction_count; d++)
    {
        // Where we're checking
        char cursor_row = row + direction_row[d];
        size_t cursor_column = column + direction_column[d];

        // Move towards the direction while we're on the opposite color
        bool found_opposite = false;
        while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
        {
            found_opposite = true;
            cursor_row += direction_row[d];
            cursor_column += direction_column[d];
        }

        // Check if the next thing after is our color
        bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);

        // If this direction is valid, the move is valid, so short circuit and return
        if (found_opposite && found_same) {
            return true;
        }
    }
    return false;
}

bool Reversi::is_game_over() const
{
    for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++)
    {
        for (size_t column = 1; column <= board_.dimension(); column++)
        {
            if (is_legal_choice(row, column, turn_))
            {
                return false;
            }
        }
    }
    return true;
}

void Reversi::save_checkpoint()
{
    Checkpoint z(board_, turn_);
    history_.push_back(z);

}

void Reversi::undo()
{
    this->turn_ = history_.back().turn_;
    this->board_ = history_.back().board_;
    history_.pop_back();

}

