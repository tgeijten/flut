#pragma once

namespace flut
{
	// WORK IN PROGRESS!
	template< typename K, typename T, typename L = void >
	class key_frame_buffer : public data_header< key_frame_buffer< K, T, L >, L >
	{
	public:
		key_frame_buffer( size_t channels = 0 ) : data_header< storage< T, L >, L >( channels ), data( channels ) {}
		~key_frame_buffer() {}

		/// add empty frame to the buffer
		void add_frame( K key, T value = T( 0 ) )
		{ data.push_back( std::make_pair( key, std::vector< T >( value, channel_count() ) ) ); }

		/// number of frames in the buffer
		size_t frame_count() { return data.size() }

		/// set a value for a channel in the most recent frame
		void set_value( index_t channel, const T& value ) { data.back() = value; }

		/// get access to the data in a specific frame
		const T* get_frame( index_t frame = frame_count() - 1 )
		{
			flut_assert( frame < frame_count() ); return &data[ frame * this->channel_count() ];
		}

		/// get the value of a specific frame / channel
		T get_value( index_t frame, index_t channel )
		{
			flut_assert( frame < frame_count() && channel < this->channel_count() ); return &data[ frame * this->channel_count() + channel ];
		}

		/// get the interpolated value of a specific frame / channel
		T get_interpolated_value( index_t frame0, index_t channel, T pos ) {
			flut_assert( frame0 + 1 < frame_count() );
			index_t ofs = frame0 * this->channel_count() + channel;
			return ( T( 1 ) - pos ) * data[ ofs ] + pos * data[ ofs + this->channel_count() ];
		}

		/// function for internal maintenance, DO NOT CALL this directly
		/// it is public because of its specific use of CRTP
		void resize_buffer() {
			data.resize( this->channel_count() );
		}

	private:
		std::vector< T > data;
	};
}
