#include "Lexer.hpp"


Token::Token(size_t type, std::string text, int index) {
    this->type = type;
    this->text = text;
    this->index = index;
}

std::ostream& operator<<(std::ostream &out, const Token& t) {
    return out << TOKEN_NAME[t.type] << " " << t.text << std::endl;
}


Lexer::Lexer(std::string src) {
    this->src = src;
    this->pos = 0;
}

std::list<Token> Lexer::lex() {

    while ([this] {
        if (this->pos >= this->src.length()) {
            return false;
        }

        for (size_t i: ITERIBLE_TOKEN_TYPES) {
            std::smatch m;
            

            std::regex r(TOKEN_REGEX[i]);
            
            std::string reg = TOKEN_REGEX[i];
            
            const std::string SEARCH_SUBSTR = this->src.substr(pos);
            const std::string MATCH_SUBSTR  = this->src.substr(pos, 1);
            
//            bool cond1 = std::regex_search(SEARCH_SUBSTR, m, r);
//            bool cond2 = std::regex_match(MATCH_SUBSTR, r);

            if (std::regex_search(SEARCH_SUBSTR, m, r) && std::regex_match(MATCH_SUBSTR, r)) {
                
                Token t(i, m.str(), this->pos);
                this->tokens.push_back(t);
                pos += m.str().length();
                
                return true;
            }

        }
        throw "Unknown symbol";
    }());
    return this->tokens;
}
