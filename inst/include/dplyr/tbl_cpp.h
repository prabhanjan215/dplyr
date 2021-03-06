#ifndef dplyr_tools_tbl_cpp_H
#define dplyr_tools_tbl_cpp_H

namespace dplyr {

    template <typename Df>
    inline void set_rownames( Df& data, int n ){
        data.attr( "row.names" ) = Rcpp::IntegerVector::create(
            Rcpp::IntegerVector::get_na(), -n) ;
    }

    template <typename Data>
    inline Rcpp::CharacterVector classes_grouped(){
        return Rcpp::CharacterVector::create( "grouped_df", "tbl_df", "tbl", "data.frame") ;
    }

    template <>
    inline Rcpp::CharacterVector classes_grouped<RowwiseDataFrame>(){
        return Rcpp::CharacterVector::create( "rowwise_df", "tbl_df", "tbl", "data.frame") ;
    }

    inline Rcpp::CharacterVector classes_not_grouped(){
        return Rcpp::CharacterVector::create( "tbl_df", "tbl", "data.frame") ;
    }

    class tbl_cpp{
    public:
        tbl_cpp( Rcpp::List data_, int nr ) : data(data_){
            set_rownames(data, nr ) ;
            data.attr( "class" ) = classes_not_grouped()  ;
        }

        inline operator SEXP(){
            return data ;
        }

    private:
        List data ;
    } ;
    
}

#endif
