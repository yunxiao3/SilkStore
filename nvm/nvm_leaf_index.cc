#include <stdexcept>
#include "nvm/nvm_leaf_index.h"
#include "util/coding.h"

namespace leveldb {
namespace silkstore {

 Iterator* NvmLeafIndex::NewIterator(const ReadOptions& options){
  //std::__throw_runtime_error(" NvmLeafIndex::NewIterator(const ReadOptions& options) not support\n");
  mutex_.Lock();         
  auto it =  nvm_table_->NewIterator();
  mutex_.Unlock();          

  if (it == nullptr){
    //std::cout<< "return NewEmptyIterator \n";
    return NewEmptyIterator();
  }
  //std::cout<< "return NvmLeafIndexIterator \n";
  return it;
} 


class EmptyKVIterator: public Iterator {
public:
  virtual void Seek(const std::string &key) {};

  virtual void SeekToFirst(){};

  virtual void SeekToLast(){};

  virtual bool Valid(){return false;};

  virtual void Next() {};

  virtual void Prev(){};

  virtual std::string Key(){return nullptr;};

  virtual std::string Value(){return nullptr;};
};


NvmLeafIndex::NvmLeafIndex(const Options& options, const std::string& dbname){
  cap_ = 10ul*1204ul*1024ul*1024ul;
  NvmManager *nvm_manager_ = new NvmManager("/mnt/NVMSilkstore/leaf_index", cap_);
    const InternalKeyComparator internal_comparator_(leveldb::BytewiseComparator());
  nvm_table_ =  new NvmemTable(internal_comparator_, nullptr, nvm_manager_->allocate(9ul*1204ul*1024ul*1024ul) );
  nvm_table_->Ref();
  printf("#### Successfully opened NvmLeafIndex #####\n");
}

Status NvmLeafIndex::OpenNvmLeafIndex(const Options& options,
                     const std::string& name,
                     DB** dbptr){
  *dbptr = new NvmLeafIndex(options, name);
  return Status::OK();
}


const Snapshot* NvmLeafIndex::GetSnapshot() {
  throw std::runtime_error("NvmLeafIndex::GetSnapshot not supported");
}

void NvmLeafIndex::ReleaseSnapshot(const Snapshot* snapshot) {
  throw std::runtime_error("NvmLeafIndex::ReleaseSnapshot not supported");
}

NvmLeafIndex::~NvmLeafIndex() {
  if (nvm_table_ != nullptr){
    nvm_table_->Unref();
  }
}


Status NvmLeafIndex::Write(const WriteOptions& options, WriteBatch* my_batch) {
  //throw std::runtime_error("NvmLeafIndex::Write not supported");
  if (nvm_table_->ApproximateMemoryUsage() > cap_){
    throw std::runtime_error("NvmLeafIndex out of memory\n");
  }
  mutex_.Lock();
  Status status = WriteBatchInternal::InsertInto(my_batch, nvm_table_);
/*  std::cout<<"########## sleep: #########\n";
  sleep(1000); */           
  mutex_.Unlock();          
  
  return status;
}


Status NvmLeafIndex::Put(const WriteOptions& options,  
             const Slice& key,
               const Slice& value) {


  std::__throw_runtime_error("");

  /* kvdk::Status s;
  mutex_.Lock();                            
  s = kv->Add(key.ToString(), value.ToString());
  mutex_.Unlock();          
  if (s == kvdk::Status::Ok){
    return Status::OK();
  }else{
    std::cout<< "NvmLeafIndex::Put ERR Code: "<< (int)s <<" \n";
    std::__throw_runtime_error(" NvmLeafIndex::Put ERR \n");
    return Status::Corruption("");  
  } */
  return Status::Corruption("");  
}

Status NvmLeafIndex::Delete(const WriteOptions& options, const Slice& key) {
  std::__throw_runtime_error("");
  /* kvdk::Status s;
  std::cout<<"Delete: " << key.ToString() << "\n";                            
  s = kv->Delete(key.ToString());
  if (s == kvdk::Status::Ok){
    return Status::OK();
  } */
  return Status::Corruption("");           
}


Status NvmLeafIndex::Get(const ReadOptions &options,
                      const Slice &key,
                      std::string *value)  {

  std::__throw_runtime_error("");
              
  /* kvdk::Status s;
  mutex_.Lock();                            
  s = kv->Get(ReadOptions(),key.ToString(), value);
  //std::cout<< key.size() <<" " << value->size() <<"\n";
  mutex_.Unlock();          

  if (s == kvdk::Status::Ok){
    return Status::OK();
  } */
  return Status::Corruption("");         
}



/* Iterator* NvmLeafIndex::NewIterator(const ReadOptions& options) {
  throw std::runtime_error("NvmLeafIndex::NewIterator not supported");
} */

bool NvmLeafIndex::GetProperty(const Slice& property, std::string* value){
  throw std::runtime_error("NvmLeafIndex::GetProperty not supported");
  return true;
}
void NvmLeafIndex::GetApproximateSizes(const Range* range, int n, uint64_t* sizes) {
  throw std::runtime_error("NvmLeafIndex::GetApproximateSizes not supported");
}
void NvmLeafIndex::CompactRange(const Slice* begin, const Slice* end) {
  throw std::runtime_error("NvmLeafIndex::CompactRange not supported");
}



}
}