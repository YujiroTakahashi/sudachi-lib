extern crate libc;
extern crate sudachiclone;

use libc::{c_void, c_int, c_char, size_t};
use std::ffi::{CString, CStr};
use sudachiclone::prelude::*;
use sudachiclone::morpheme::Morpheme;

#[repr(C)]
pub struct sudachi_node {
    surface: size_t, 
    pos: size_t,
    normalized_form: size_t,
    dictionary_form: size_t,
    reading_form: size_t,
    data: *const c_char,
}

#[no_mangle]
pub extern "C" fn new_tokenizer(c_path: *const c_char) -> *mut c_void {
    let path = unsafe {
        CStr::from_ptr(c_path).to_str().unwrap().to_string()
    };
    let dictionary = Dictionary::setup(Some(&path), None).unwrap();
    let tokenizer = dictionary.create();
    Box::into_raw(Box::new(tokenizer)) as *mut c_void
}

#[no_mangle]
pub extern "C" fn free_tokenizer(ptr: *mut Tokenizer) {
    unsafe {
        if ptr.is_null() {
            return;
        }
        Box::from_raw(ptr)
    };
}

#[no_mangle]
pub extern "C" fn parse_tokenizer(ptr: *mut Tokenizer, input: *const c_char) -> *mut c_void {
    let text = unsafe {
        CStr::from_ptr(input).to_str().unwrap().to_string()
    };
    let list = unsafe {
        (*ptr).tokenize(&text, &Some(SplitMode::C), None).unwrap()
    };
    let mut result:Vec<Morpheme> = Vec::new();
    for node in list {
        result.push(node);
    }

    Box::into_raw(Box::new(result)) as *mut c_void
}

#[no_mangle]
pub extern "C" fn size_morpheme_list(ptr: *mut Vec<Morpheme>) -> c_int {
    unsafe {
        if ptr.is_null() {
            return 0
        }
        (*ptr).len() as c_int
    }
}


#[no_mangle]
pub extern "C" fn free_morpheme_list(ptr: *mut Vec<Morpheme>) {
    unsafe {
        if ptr.is_null() {
            return;
        }
        Box::from_raw(ptr)
    };
}

#[no_mangle]
pub extern "C" fn get_node(ptr: *mut Vec<Morpheme>, idx: *const c_int) -> *mut c_void {
    let morpheme = unsafe {
        assert!(!ptr.is_null());
        &(*ptr)[idx as usize]
    };

    let str_node = format!("{}{}{}{}{}",
        morpheme.surface(),
        morpheme.part_of_speech().join(","),
        morpheme.normalized_form(),
        morpheme.dictionary_form(),
        morpheme.reading_form(),
    ).to_string();

    let node = sudachi_node {
        surface: morpheme.surface().len(), 
        pos: morpheme.part_of_speech().join(",").len(),
        normalized_form: morpheme.normalized_form().len(),
        dictionary_form: morpheme.dictionary_form().len(),
        reading_form: morpheme.reading_form().len(),
        data: CString::new(str_node).unwrap().into_raw(),
    };

    Box::into_raw(Box::new(node)) as *mut c_void
}

#[no_mangle]
pub extern "C" fn free_node(ptr: *mut sudachi_node) {
    unsafe {
        if ptr.is_null() {
            return;
        }
        free_string((*ptr).data as *mut i8);
        Box::from_raw(ptr);
    };
}

pub fn free_string(ptr: *mut i8) {
    unsafe {
        if ptr.is_null() {
            return;
        }
        CString::from_raw(ptr)
    };
}
