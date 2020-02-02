#include "Lexer.hpp"

std::ostream& operator<<(std::ostream &out, const Token& t) {
    return out << TOKEN_NAME[t.type] << " " << t.text << " " << t.pos_in_text.first << " : " << t.pos_in_text.second << std::endl;
}

std::list<Token> Lexer::lex() {

    while ([this] {
        if (pos >= src.length()) {
            return false;
        }
        
        for (size_t i: ITERIBLE_TOKEN_TYPES) {
            std::smatch m;
            
            std::regex r(TOKEN_REGEX[i]);
            std::regex string_r("[a-zA-Z]*");
            
            std::string reg = TOKEN_REGEX[i];
            
            const std::string SEARCH_SUBSTR = src.substr(pos);
            const std::string MATCH_SUBSTR  = src.substr(pos, std::regex_match(TOKEN_REGEX[i], string_r) ? strlen(TOKEN_NAME[i]) : 1);

            if (std::regex_search(SEARCH_SUBSTR, m, r) && std::regex_match(MATCH_SUBSTR, r)) {
                
                if (i == NEXT_LINE) {
                    row++;
                    symbol = 1;
                } else {
                    symbol += m.str().length();
                }
                
                Token t(i, m.str(), std::make_pair(row, symbol));

                tokens.push_back(t);
                pos += m.str().length();
                
                return true;
            }
        }
        throw std::make_tuple("Unknown symbol", "Lexer::lex()", std::make_pair(row, symbol));
    }());
    return tokens;
}
