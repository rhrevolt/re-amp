#ifndef SINGLETON_H
#define SINGLETON_H

template <class T> class Singleton
{
	public :
		inline static T* getInstance() {
			if (!s_pInstance)
				s_pInstance = new T;

			return s_pInstance;
		}

		inline static void DestroyInstance() {
			if(s_pInstance) delete s_pInstance;
			s_pInstance = 0;
		}

	protected :
		Singleton() {}
		~Singleton() {}

	private :
		static T* s_pInstance;	// Instance de la classe

		Singleton(Singleton&);
		void operator =(Singleton&);
};


template <class T> T* Singleton<T>::s_pInstance = 0;

#endif // SINGLETON_H

