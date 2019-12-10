#include "Lexer.hpp"

std::ostream& operator<<(std::ostream &out, const Token& t) {
    return out << t.pos << " " << TOKEN_NAME[t.type] << " " << t.text << std::endl;
}


Lexer::Lexer(std::string src) {
    this->src = src;
    this->pos = 0;
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
                
                Token t(i, m.str(), pos);
                tokens.push_back(t);
                pos += m.str().length();
                
                return true;
            }
        }
        throw "Unknown symbol";
    }());
    return tokens;
}

