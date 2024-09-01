import nltk
nltk.download('stopwords')
nltk.download('wordnet')

from nltk.corpus import stopwords
from nltk.tokenize.toktok import ToktokTokenizer
from nltk.stem import WordNetLemmatizer 

import re

import string


def remove_stopwords(text: str) -> str:
    '''
    E.g.,
        text: 'Here is a dog.'
        preprocessed_text: 'Here dog.'
    '''
    stop_word_list = stopwords.words('english')
    tokenizer = ToktokTokenizer()
    tokens = tokenizer.tokenize(text)
    tokens = [token.strip() for token in tokens]
    filtered_tokens = [token for token in tokens if token.lower() not in stop_word_list]
    preprocessed_text = ' '.join(filtered_tokens)

    return preprocessed_text


def preprocessing_function(text: str) -> str:
    preprocessed_text = remove_stopwords(text)
    
    # TO-DO 0: Other preprocessing function attemption
    # Begin your code
    '''
    remove <br>
    '''
    regex=re.compile(r'<[^>]+>')
    preprocessed_text = regex.sub('',preprocessed_text)
    '''
    remove 標點符號
    '''
    preprocessed_text=preprocessed_text.translate(str.maketrans('', '', string.punctuation))

    '''
    lowercase (大寫換小寫) 
    '''
    preprocessed_text = ' '.join([word.lower() for word in preprocessed_text.rstrip().split()])
    '''
    lemmatize(字根化)
    '''
    lem = WordNetLemmatizer()
    preprocessed_text = ' '.join([lem.lemmatize(word, 'n') for word in preprocessed_text.rstrip().split()])
    preprocessed_text = ' '.join([lem.lemmatize(word, 'v') for word in preprocessed_text.rstrip().split()])
    preprocessed_text = ' '.join([lem.lemmatize(word, 'a') for word in preprocessed_text.rstrip().split()])
    preprocessed_text = ' '.join([lem.lemmatize(word, 's') for word in preprocessed_text.rstrip().split()])
    preprocessed_text = ' '.join([lem.lemmatize(word, 'r') for word in preprocessed_text.rstrip().split()])
    
    
    # End your code

    return preprocessed_text