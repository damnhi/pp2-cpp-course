#pragma once

#include <iosfwd>
#include <string>
#include <cstddef> // std::size_t
#include <memory>  // std::unique_ptr
#include <fstream>


/** @file FileMatrix.hpp
    @date 16 kwietnia 2023
    @brief W ramach zadania trzeba zaimplementowac wszystkie opisane metody szablonu klasy FileMatrix.
    Do ponizszych metod **sa testy** w pliku @ref FileMatrixTests.cpp.
    FileMatrix jest szablonem klasy, dlatego też musi mieć implementacje w pliku nagłówkowym,
    oczywiście polecam dłuższych metod nie definiować w klasie, tylko pod nią.
    Jeśli by ktoś chciał mimo wszystko dokonać definicji w pliku źródłowym,
    może zastosować tzw. [Explicit instantiation definition](https://en.cppreference.com/w/cpp/language/class_template)
    **dla każdego z typów!**
**/

//#define UNDEFINED_FILE_MATRIX_ITERATOR


/** class FileMatrix
 * @brief Szablon klasy FileMatrix jest macierzą elementów o określonym typie,
 * ale trudność polega na tym, że z założenia jest ona w stanie trzymać macierz nie mieszczącą się w pamięci,
 * poprzez trzymanie wszystkich danych na dysku, a w aktualnej pamięci podręcznej jest tylko jeden rząd danych.
 * Dane trzymane na dysku są w formacie **binarnym**, w następującej formie:
 * 1. `IndexType rows_`
 * 2. `IndexType columns_`
 * 3. `T[]` - dane zależnie od ich ilości, będzie to `rows_*columns_`
 *
 * @note Można (a nawet należy) zaimplementować dodatkowe metody.
 * @note Można (a nawet wygodniej) dodać dodatkowe składowe klasy
 *       (niewykluczone użycie kwantyfikatora `mutable`)
 *
 * @tparam T typ przetrzymywany w macierzy
 * @tparam IndexType typ do indeksowania elementow, ten typ powinien byc uzyty do skladowych `rows_`, `columns_`
 *
 * @param filename_ pełna nazwa pliku (czyli wraz ze ścieżką i rozszerzeniem)
 * @param rows_ ilość rzędów w macierzy prostokątnej
 * @param columns_ ilość kolumn w macierzy prostokątnej
 * @param currentRow_ jest to ostatnio odczytywany rząd macierzy,
 *        dzięki niemu możemy ograniczyć lekko operacje dyskowe
 * @param currentRowNumber_ informacja którym rzędem jest powyższy
 * @param fileDescriptor_ deskryptor pliku o nazwie `filename_`,
 *        nie musimy za każdym razem na nowo otwierać i zamykać pliku (to trwa) **/
template<typename T, typename IndexType = std::size_t>
class FileMatrix
{
public:
    static constexpr auto extention()
    {
        return ".matrix";
    }

    /// @brief konstruktor przyjmujący nazwę pliku, wystarczy, że zapamięta on ją w zmiennej `filename_` i wyzeruje zmienne klasy
    FileMatrix(const std::string& filename): filename_(filename)
    {}

    /** @brief konstruktor przyjmujący poza nazwą pliku również informacje
     *  ile jest wierszy i kolumn, tym samym powinien on utworzyć plik
     *  i wypełnić go zawartością **/
    FileMatrix(IndexType rows, IndexType columns, const std::string& newFileName);

    /** @brief konstruktor kopiujący, który powinien utworzyć nowy plik
     *  w tym samym katalogu i o nazwie niemalże identycznej jak `sourceMatrix.filename_`
     *  nazwą pliku ale z suffixem: `_copy` np.:
     *  `path/to/file/matrix100x100.matrix` -> `path/to/file/matrix100x100_copy.matrix`
     *  Zawartość dwóch plików powinna być dokładnie taka sama (zgodność binarna) **/
    FileMatrix(const FileMatrix& sourceMatrix){

        if (this == &sourceMatrix) {
            return;
        }

        if (fileDescriptor_.is_open()) {
            fileDescriptor_.close();
        }


        std::string file_extenstion = ".matrix";
        size_t found_index = sourceMatrix.filename_.find(file_extenstion);
        if (found_index == std::string::npos) throw std::runtime_error("Value is not found(copy)");
        std::string new_filename = sourceMatrix.filename_;
        new_filename.insert(found_index, "_copy");

        filename_ = new_filename;
        rows_ = sourceMatrix.rows_;
        columns_ = sourceMatrix.columns_;
        currentRowNumber_ = sourceMatrix.currentRowNumber_;


        std::ifstream source(sourceMatrix.filename_, std::ios::binary);
        if (!source.is_open()) throw std::runtime_error("Failed to open file.(copy)");

        fileDescriptor_.open(filename_, std::ios::binary | std::ios::out);
        if (!fileDescriptor_.is_open()) throw std::runtime_error("Failed to open file.(copy)");

        fileDescriptor_ << source.rdbuf();

        source.close();

        fileDescriptor_.seekg(currentRowNumber_ * columns_ * sizeof(T));

        currentRow_ = std::make_unique<T[]>(columns_);
        fileDescriptor_.read(reinterpret_cast<char*>(currentRow_.get()), columns_ * sizeof(T));
    }

    /** @brief konstruktor przenoszący, który zmienić nazwę pliku `sourceMatrix.filename_`
     *  na taki zawierający nazwę z suffixem `_move` w tym samym katalogu
     *  i o nazwie niemalże identycznej np.:
     *  `path/to/file/matrix100x100.matrix` -> `path/to/file/matrix100x100_move.matrix`
     *  `sourceMatrix` powinien być wyczyszczony jak w stanie po zawołaniu
     *  konstruktora przyjmującego jedynie nazwę pliku.
     *  Plik `filename_` nie musi istnieć, ale obiekt
     *  powinien się nadawać do dalszego użytkowania. **/
    FileMatrix(FileMatrix&& sourceMatrix){

        if (this == &sourceMatrix) {
            return;
        }

        if (fileDescriptor_.is_open()) {
            fileDescriptor_.close();
        }


        std::string file_extenstion = ".matrix";
        size_t found_index = sourceMatrix.filename_.find(file_extenstion);
        if (found_index == std::string::npos) throw std::runtime_error("Value is not found");
        std::string new_filename = sourceMatrix.filename_;
        new_filename.insert(found_index, "_move");

        filename_ = new_filename;
        rows_ = sourceMatrix.rows_;
        columns_ = sourceMatrix.columns_;
        currentRowNumber_ = sourceMatrix.currentRowNumber_;


        std::ifstream source(sourceMatrix.filename_, std::ios::binary);
        if (!source.is_open()) throw std::runtime_error("Failed to open source file.");

        std::ofstream new_file;
        new_file.open(filename_, std::ios::binary);

        if (!new_file.is_open()) throw std::runtime_error("Failed to open new file.");

        new_file << source.rdbuf();

        source.close();


//        fileDescriptor_.seekg(currentRowNumber_ * columns_ * sizeof(T));
//
//        current_row = std::make_unique<T[]>(columns_);
//        fileDescriptor_.read(reinterpret_cast<char*>(current_row.get()), columns_ * sizeof(T));

        sourceMatrix.columns_ = 0;
        sourceMatrix.rows_ = 0;
        sourceMatrix.currentRow_ = nullptr;
        sourceMatrix.currentRowNumber_ = 0;
        fileDescriptor_.flush();
//        sourceMatrix.fileDescriptor_ = 0;

        if (std::remove(sourceMatrix.filename_.c_str()) != 0) throw std::runtime_error("Failed to delete file");
        sourceMatrix.fileDescriptor_.close();
//        if (std::remove(sourceMatrix.filename_.c_str()) != 0 ) throw std::runtime_error("Error deleting file");
//        sourceMatrix.fileDescriptor_.close();
    };

    /** @brief destruktor - powinien przede wszystkim posprzątać zasoby, które się same nie posprzątają **/
    ~FileMatrix(){};

    /** @brief operator przypisania kopiujący, po jego zawołaniu plik
     *  `filename_` powinien mieć zawartość binarnie identyczną do `sourceMatrix.filename_` **/
    FileMatrix& operator=(const FileMatrix& sourceMatrix){

        if (this == &sourceMatrix) {
            return *this;
        }

        if (fileDescriptor_.is_open()) {
            fileDescriptor_.close();
        }

    // new name of variable
        std::string file_extenstion = ".matrix";
        size_t found_index = sourceMatrix.filename_.find(file_extenstion);
        if (found_index == std::string::npos) throw std::runtime_error("Value is not found(copy_operator)");
        std::string new_filename = sourceMatrix.filename_;
        new_filename.insert(found_index, "_copy");


        filename_ = new_filename;
        rows_ = sourceMatrix.rows_;
        columns_ = sourceMatrix.columns_;
        currentRowNumber_ = sourceMatrix.currentRowNumber_;


        std::ifstream source(sourceMatrix.filename_, std::ios::binary);
        if (!source.is_open()) throw std::runtime_error("Failed to source open file.(copy_operator)");

        fileDescriptor_.open(filename_, std::ios::binary | std::ios::out);
        if (!fileDescriptor_.is_open()) throw std::runtime_error("Failed to open new file.(copy_operator)");

        fileDescriptor_ << source.rdbuf();

        source.close();

        fileDescriptor_.seekg(currentRowNumber_ * columns_ * sizeof(T));

        currentRow_ = std::make_unique<T[]>(columns_);
        fileDescriptor_.read(reinterpret_cast<char*>(currentRow_.get()), columns_ * sizeof(T));

        return *this;
    };

    /** @brief operator przypisania przenoszący, po jego zawołaniu plik
     *  `filename_` powinien mieć zawartość dokładnie taką jak `sourceMatrix.filename_`
     *  (najprościej zrobić `rename()` na plikach).
     *  Z kolei plik `filename_` nie musi istnieć, ale obiekt
     *  powinien się nadawać do dalszego użytkowania. **/
    FileMatrix& operator=(FileMatrix&& sourceMatrix){
        if (this == &sourceMatrix) {
            return *this;
        }

        if (fileDescriptor_.is_open()) {
            fileDescriptor_.close();
        }


        std::string file_extenstion = ".matrix";
        size_t found_index = sourceMatrix.filename_.find(file_extenstion);
        if (found_index == std::string::npos) throw std::runtime_error("Value is not found");
        std::string new_filename = sourceMatrix.filename_;
        new_filename.insert(found_index, "_move");

        filename_ = new_filename;
        rows_ = sourceMatrix.rows_;
        columns_ = sourceMatrix.columns_;
        currentRowNumber_ = sourceMatrix.currentRowNumber_;


        std::ifstream source(sourceMatrix.filename_, std::ios::binary);
        if (!source.is_open()) throw std::runtime_error("Failed to open file.");

        fileDescriptor_.open(filename_, std::ios::binary | std::ios::out);
        if (!fileDescriptor_.is_open()) throw std::runtime_error("Failed to open file.");

        fileDescriptor_ << source.rdbuf();

        source.close();

        fileDescriptor_.seekg(currentRowNumber_ * columns_ * sizeof(T));

        currentRow_ = std::make_unique<T[]>(columns_);
        fileDescriptor_.read(reinterpret_cast<char*>(currentRow_.get()), columns_ * sizeof(T));
        fileDescriptor_.flush();

        sourceMatrix.columns_ = 0;
        sourceMatrix.rows_ = 0;
        sourceMatrix.currentRow_ = nullptr;
        sourceMatrix.currentRowNumber_ = 0;
//        sourceMatrix.fileDescriptor_.close();
        if (std::remove(sourceMatrix.filename_.c_str()) != 0 ) throw std::runtime_error("Error deleting file");

        sourceMatrix.fileDescriptor_.close();
        return *this;
    };

    auto rows() const
	{
        return rows_;
	}

    auto columns() const
	{
        return columns_;
	}

    const auto& filename() const
	{
        return filename_;
	}

    /** @brief operator indeksowania, który zwraca wskaźnik do wskazanego wiersza macierzy.
     *  W razie jeśli w pamięci jest inny należy zrzucić jego dane na dysk i wczytać właściwy wiersz, następnie go zwrócić.
     *  @note Tym sposobem zadziała zawołanie `matrix[row][column]`,
     *        jednakże nie jesteśmy w stanie sprawdzić, czy `column` nie wychodzi poza zakres
     *  **/
    T* operator[](IndexType indexOfRow);

    /** @brief operator indeksowania stały, analogiczny jak operator indeksowania niestały.
     *  @note Aby on działał w analogiczny sposób pewne składowe zapewne będą musiały mieć przedrostem `mutable`. **/
    const T* operator[](IndexType indexOfRow) const;

    bool operator==(const FileMatrix& matrix) const{
        std::ifstream stream1(filename_, std::ios::binary | std::ios::ate);
        std::ifstream stream2(matrix.filename_, std::ios::binary | std::ios::ate);

        if(!stream1.is_open() || !stream2.is_open()){
            return false;
        }

//        if (!stream1.is_open() || !stream2.is_open()) {
//            throw std::runtime_error("Failed to open file(== operator)");
//        }
        stream1.seekg(0);
        stream2.seekg(0);

        char byte1, byte2;
        while (stream1.get(byte1) && stream2.get(byte2)) {
            if (byte1 != byte2) {

                return false;
            }
        }

        return true;

    };

	bool operator!=(const FileMatrix& matrix) const
	{
		return !((*this) == matrix);
	}

    /** @brief operator mnożenia całej macierzy przez wartość **/
    FileMatrix& operator*=(const T& value){};

    /** @brief metoda zrzucająca aktualnie trzymany wiersz w pamięci na dysk.
     *  @note zalecam też aby wołała `fstream::flush()`, aby buforowalne dane zostały mimo wszystko od razu wrzucone na dysk **/
    void flush(){
        if (currentRow_)
        {
            fileDescriptor_.open(filename_, std::ios::binary | std::ios::in| std::ios::out);
            if(!fileDescriptor_.is_open()) throw std::runtime_error("Failed to open in flush");
            fileDescriptor_.seekp(sizeof(T)*columns_*currentRowNumber_ + 2*sizeof(IndexType),std::ios::beg);
            fileDescriptor_.write(reinterpret_cast<char*>(currentRow_.get()), sizeof(T) * columns_);
            fileDescriptor_.flush();
            fileDescriptor_.close();
        }

    };


    /** @brief iterator umożliwiający przeglądanie danych idąc wierszami, a następnie w każdym wierszu do każdej kolumny.
     *  Wystarczy, żeby to był iterator jednokierunkowy.
     *  @note Jeśli go zdefiniujesz zdefiniuj makro: `#define FILE_MATRIX_ITERATOR_DEFINED 1` **/
    struct iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;

        iterator(FileMatrix<T, IndexType>& matrix, IndexType row = 0, IndexType col = 0)
        : matrix_(matrix), current_row(row), current_col(col) {}

        reference operator*() const { return matrix_[current_row][current_col]; }

        iterator& operator++() {
            if (current_row == matrix_.rows_ && current_col == matrix_.columns_) {
                throw std::out_of_range("iterator out of range");
            }
            if (current_row > matrix_.rows_) throw std::out_of_range("iterator out of range");

            if (matrix_.columns_ <= current_col + 1) {
                current_row++;
                current_col = 0;
            } else {
                current_col++;
            }

            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            if (current_row == matrix_.rows_ && current_col == matrix_.columns_){
                throw std::out_of_range("iterator out of range");
            }
            if (current_row > matrix_.rows_) throw std::out_of_range("iterator out of range");

            if(matrix_.columns_ <= current_col + 1){
                current_row++;
                current_col = 0;
            }
            else {
                current_col++;
            }
            return old;
        }

        bool operator==(const iterator& other) const {
            return current_row == other.current_row && current_col == other.current_col;
        }

        bool operator!=(const iterator& other) const {
            return current_row != other.current_row || current_col != other.current_col;
        }

    private:
        FileMatrix<T, IndexType>& matrix_;
        IndexType current_row;
        IndexType current_col;
    };


    iterator begin() {
        return iterator(*this, 0 ,0);
    }

    iterator end() {
        return iterator(*this, rows_, 0);
    }

private: // methods:
    // TODO: zaimplementuj jesli cos potrzeba

private: // fields:
    std::string filename_;

    IndexType rows_{}, columns_{};

    mutable std::fstream fileDescriptor_;

    mutable std::unique_ptr<T[]> currentRow_;
    mutable IndexType currentRowNumber_{};
};

template<typename T, typename IndexType>
T *FileMatrix<T, IndexType>::operator[](IndexType indexOfRow) {

    if(indexOfRow>=rows_){
        throw std::out_of_range("Row index is out of range");
    }

    if(currentRow_){
        flush();
    }
    fileDescriptor_.open(filename_, std::ios::binary | std::ios::in| std::ios::out);

    std::unique_ptr<T[]> row_buff(new T[columns_]);

    fileDescriptor_.seekg(sizeof(T)*columns_*indexOfRow+ 2*sizeof(IndexType) ,std::ios::beg);
    fileDescriptor_.read(reinterpret_cast<char*>(row_buff.get()), sizeof(T) * columns_);
    currentRowNumber_ = indexOfRow;
    currentRow_.reset();
    currentRow_ = std::move(row_buff);
    fileDescriptor_.close();

    return currentRow_.get();
}

template<typename T, typename IndexType>
const T *FileMatrix<T, IndexType>::operator[](IndexType indexOfRow) const {


    if(indexOfRow>rows_){
        throw std::out_of_range("Row index is out of range");
    }
    if (currentRow_)
    {
        fileDescriptor_.open(filename_, std::ios::binary | std::ios::in| std::ios::out);
        fileDescriptor_.seekp(sizeof(T)*columns_*currentRowNumber_ + 2*sizeof(IndexType),std::ios::beg);
        fileDescriptor_.write(reinterpret_cast<char*>(currentRow_.get()), sizeof(T) * columns_);
        fileDescriptor_.flush();
        fileDescriptor_.close();
    }
    fileDescriptor_.open(filename_, std::ios::binary | std::ios::in| std::ios::out);


    std::unique_ptr<T[]> row_buff(new T[columns_]);

    fileDescriptor_.seekg(sizeof(T)*columns_*(indexOfRow-1)+ 2*sizeof(IndexType) ,std::ios::beg);
    fileDescriptor_.read(reinterpret_cast<char*>(row_buff.get()), sizeof(T) * columns_);
    currentRowNumber_ = indexOfRow;
    currentRow_.reset();
    currentRow_ = std::move(row_buff);
    fileDescriptor_.close();

    return currentRow_.get();
}



template<typename T, typename IndexType>
FileMatrix<T, IndexType>::FileMatrix(IndexType rows, IndexType columns, const std::string &newFileName):rows_(rows), columns_(columns),
                                                                                                       filename_(newFileName) {
    fileDescriptor_.open(newFileName, std::ios::binary | std::ios::out);

    if (!fileDescriptor_.is_open())
    {
        throw std::runtime_error("matrix file: " + newFileName + " is opened.");
    }


    fileDescriptor_.write(reinterpret_cast<const char*>(&rows), sizeof(IndexType));
    fileDescriptor_.write(reinterpret_cast<const char*>(&columns), sizeof(IndexType));

    T value_of_given_type{};
    for (IndexType i = 0; i < rows*columns; ++i)
    {

        fileDescriptor_.write(reinterpret_cast<const char*>(&value_of_given_type), sizeof(T));
    }

    fileDescriptor_.close();




}
